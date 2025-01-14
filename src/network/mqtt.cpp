#include "mqtt.h"
#include "../protocol/compiled/messages.h"
#include "../renderer/message.h"
#include "../utils/debug.h"

#include <WiFi.h>
#include <WiFiClientSecure.h>

using namespace network;

const char* kAlpnProtocols[2] = {"mqtt", nullptr};
const uint16_t kKeepAlivePeriod = 5;
const uint16_t kSocketTimeout = 8;
const uint32_t kReconnectDelay = 5;
const std::string kSetMessageTopicSuffix = "/message";
const std::string kSetBackgroundMessageTopicSuffix = "/background";
const uint16_t kMqttBufferSize = 0x1000;

class VectorReadBufferInterface : public ::EmbeddedProto::ReadBufferInterface {
 public:
  VectorReadBufferInterface(const std::vector<uint8_t>& data)
      : data_(data), index_(0) {}

  virtual ~VectorReadBufferInterface() = default;

  virtual uint32_t get_size() const { return this->data_.size(); }

  virtual uint32_t get_max_size() const { return this->data_.size(); }

  virtual bool peek(uint8_t& byte) const {
    if (this->index_ >= this->data_.size()) {
      return false;
    }
    byte = this->data_[index_];
    return true;
  }

  virtual bool advance() {
    if ((this->index_ + 1) >= this->data_.size()) {
      return false;
    }
    this->index_++;
    return true;
  }

  virtual bool advance(const uint32_t n_bytes) {
    if ((this->index_ + n_bytes) >= this->data_.size()) {
      return false;
    }
    this->index_ += n_bytes;
    return true;
  }

  virtual bool pop(uint8_t& byte) {
    if (this->index_ >= this->data_.size()) {
      return false;
    }
    byte = this->data_[this->index_++];
    return true;
  }

 private:
  std::vector<uint8_t> data_;
  uint32_t index_;
};

void Mqtt::Init() {
  this->secure_client_.setAlpnProtocols(kAlpnProtocols);
  this->secure_client_.setTimeout(kSocketTimeout);
  this->secure_client_.setCACert(this->ca_certificate_.c_str());
  this->mqtt_client_.setKeepAlive(kKeepAlivePeriod);
  this->mqtt_client_.setSocketTimeout(kSocketTimeout);
  this->mqtt_client_.setBufferSize(kMqttBufferSize);
  this->mqtt_client_.setCallback(
      [&](const char* raw_topic, const uint8_t* raw_data, uint32_t length) {
        DEBUG_PRINT_PREFIX("MQTT recieved from '%s'\n", raw_topic);
        const std::string topic(raw_topic);
        const std::vector<uint8_t> data(raw_data, raw_data + length);
        if (topic == this->base_topic_ + kSetMessageTopicSuffix) {
          this->ProcessSetMessage(data);
        }
        if (topic == this->base_topic_ + kSetBackgroundMessageTopicSuffix) {
          this->ProcessSetBackgroundMessage(data);
        }
      });
}

void Mqtt::MqttTask(void* raw_mqtt_client) {
  const auto mqtt_client = static_cast<Mqtt*>(raw_mqtt_client);
  while (true) {
    DEBUG_PRINT_PREFIX("Connecting to MQTT...\n");
    if (!mqtt_client->Connect()) {
      DEBUG_PRINT_PREFIX("Failed to connect to MQTT, reconnecting\n");
      vTaskDelay(pdMS_TO_TICKS(kReconnectDelay * 1000));
      continue;
    }
    DEBUG_PRINT_PREFIX("Connected to MQTT\n");
    while (mqtt_client->mqtt_client_.connected() &&
           mqtt_client->secure_client_.connected()) {
      if (!mqtt_client->mqtt_client_.loop()) {
        break;
      }
    }
    mqtt_client->Disconnect();
  }
}

bool Mqtt::Start() {
  this->Init();
  if (xTaskCreate(Mqtt::MqttTask, "mqtt-task", 0x2000, this, 2,
                  &this->mqtt_task_) != pdPASS) {
    this->mqtt_task_ = nullptr;
    return false;
  }
  return true;
}

void Mqtt::Stop() {
  if (this->mqtt_task_) {
    vTaskDelete(this->mqtt_task_);
  }
  this->Disconnect();
}

Mqtt::~Mqtt() {
  this->Stop();
}

bool Mqtt::Connect() {
  if (!::WiFi.isConnected()) {
    DEBUG_PRINT_PREFIX("WiFi is not connected, not connecting\n");
    return false;
  }
  if (!this->secure_client_.connect(this->host_.c_str(), this->port_)) {
    DEBUG_PRINT_PREFIX("Failed to connect to TLS socket\n");
    return false;
  }
  if (!this->mqtt_client_.connect("bksp-signage", this->username_.c_str(),
                                  this->password_.c_str())) {
    DEBUG_PRINT_PREFIX("Failed to connect to MQTT server\n");
    return false;
  }
  if (!this->mqtt_client_.subscribe(
          (this->base_topic_ + kSetBackgroundMessageTopicSuffix).c_str(), 0)) {
    DEBUG_PRINT_PREFIX(
        "Failed to subscribe to '%s'\n",
        (this->base_topic_ + kSetBackgroundMessageTopicSuffix).c_str());
    return false;
  }
  if (!this->mqtt_client_.subscribe(
          (this->base_topic_ + kSetMessageTopicSuffix).c_str(), 0)) {
    DEBUG_PRINT_PREFIX("Failed to subscribe to '%s'\n",
                       (this->base_topic_ + kSetMessageTopicSuffix).c_str());
    return false;
  }
  return true;
}

template <uint32_t T>
bool ParseProtoMessage(const protocol::Message<T>& proto_message,
                       renderer::Message& message) {
  if (!proto_message.data()) {
    return false;
  }

  message.brightness = proto_message.get_brightness();
  message.effect_type =
      static_cast<renderer::EffectType>(proto_message.get_effect_type());
  message.data =
      std::vector<uint8_t>(proto_message.get_data().get_const(),
                           proto_message.get_data().get_const() +
                               proto_message.get_data().get_length());
  switch (proto_message.get_effect_type()) {
    case protocol::EffectType::STATIC: {
      if (!proto_message.has_static_effect()) {
        return false;
      }
      message.effect.static_effect.position = static_cast<renderer::Position>(
          proto_message.get_static_effect().get_position());
      break;
    }
    case protocol::EffectType::FLASH: {
      if (!proto_message.has_flash_effect()) {
        return false;
      }
      message.effect.flashing_effect.position = static_cast<renderer::Position>(
          proto_message.get_flash_effect().get_position());
      message.effect.flashing_effect.delay =
          proto_message.get_flash_effect().get_delay();
      break;
    }
    case protocol::EffectType::SCROLL: {
      if (!proto_message.has_scroll_effect()) {
        return false;
      }
      message.effect.scroll_effect.direction = static_cast<renderer::Direction>(
          proto_message.get_scroll_effect().get_direction());
      message.effect.scroll_effect.speed =
          proto_message.get_scroll_effect().get_speed();
      break;
    }
  }

  return true;
}

void Mqtt::ProcessSetMessage(const std::vector<uint8_t>& data) {
  DEBUG_PRINT_PREFIX("Processing SetMessagePacket\n");
  std::unique_ptr<protocol::SetMessagePacket<MAX_MESSAGE_DATA_LENGTH>> packet(
      new protocol::SetMessagePacket<MAX_MESSAGE_DATA_LENGTH>());
  VectorReadBufferInterface response_interface(data);
  if (packet->deserialize(response_interface) !=
      ::EmbeddedProto::Error::NO_ERRORS) {
    return;
  }

  renderer::Message message;
  if (!ParseProtoMessage(packet->get_message(), message)) {
    return;
  }

  this->renderer_->SetMessage(message, packet->get_priority(),
                              packet->get_duration());
}

void Mqtt::ProcessSetBackgroundMessage(const std::vector<uint8_t>& data) {
  DEBUG_PRINT_PREFIX("Processing SetBackgroundMessagePacket\n");
  std::unique_ptr<protocol::SetBackgroundMessagePacket<MAX_MESSAGE_DATA_LENGTH>> packet(
    new protocol::SetBackgroundMessagePacket<MAX_MESSAGE_DATA_LENGTH>
  );
  VectorReadBufferInterface response_interface(data);
  if (packet->deserialize(response_interface) !=
      ::EmbeddedProto::Error::NO_ERRORS) {
    return;
  }

  renderer::Message message;
  if (!ParseProtoMessage(packet->get_message(), message)) {
    return;
  }

  this->renderer_->SetBackgroundMessage(message);
}

void Mqtt::Disconnect() {
  this->mqtt_client_.disconnect();
  this->secure_client_.stop();
  DEBUG_PRINT_PREFIX("Disconnected from MQTT\n");
}
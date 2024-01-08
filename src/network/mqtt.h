#ifndef NETWORK_MQTT_H_
#define NETWORK_MQTT_H_

#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <string>
#include <vector>
#include <memory>

#include "../renderer/renderer.h"

#define MAX_MESSAGE_DATA_LENGTH 0x1000

namespace network {

class Mqtt {
 public:
  Mqtt(const std::string& host, uint16_t port,
       const std::string& ca_certificate, const std::string& username,
       const std::string& password, const std::string& base_topic, std::shared_ptr<renderer::Renderer> renderer)
      : host_(host),
        port_(port),
        ca_certificate_(ca_certificate),
        username_(username),
        password_(password),
        base_topic_(base_topic),
        mqtt_client_(secure_client_),
        renderer_(renderer),
        mqtt_task_(nullptr){};

  bool Start();
  void Stop();

  ~Mqtt();

 private:
  void Init();
  bool Connect();
  void Disconnect();
  void ProcessSetMessage(const std::vector<uint8_t>& data);
  void ProcessSetBackgroundMessage(const std::vector<uint8_t>& data);

  static void MqttTask(void* raw_mqtt_client);

  std::string host_;
  uint16_t port_;
  std::string ca_certificate_;
  std::string username_;
  std::string password_;
  std::string base_topic_;
  std::shared_ptr<renderer::Renderer> renderer_;

  WiFiClientSecure secure_client_;
  PubSubClient mqtt_client_;

  TaskHandle_t mqtt_task_;
};

}  // namespace network

#endif  //NETWORK_MQTT_H_
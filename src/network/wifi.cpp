#include "wifi.h"
#include "../utils/debug.h"

#include <WiFi.h>

const uint32_t kReconnectDelay = 5;

bool network::WiFi::Connect() {
  ::WiFi.mode(WIFI_MODE_STA);
  ::WiFi.begin(this->ssid_.c_str(), this->password_.c_str());
  return ::WiFi.waitForConnectResult() == WL_CONNECTED;
}

void network::WiFi::WiFiTask(void* raw_wifi) {
  const auto wifi = static_cast<network::WiFi*>(raw_wifi);

  while (true) {
    DEBUG_PRINT_PREFIX("Connecting to WiFi...\n");
    if (!wifi->Connect()) {
      DEBUG_PRINT_PREFIX("Failed to connect to WiFi, reconnecting\n");
      vTaskDelay(pdMS_TO_TICKS(kReconnectDelay * 1000));
      continue;
    }
    DEBUG_PRINT_PREFIX("Connected to WiFi\n");
    if (!wifi->mqtt_->Start()) {
      DEBUG_PRINT_PREFIX("Failed to start MQTT task\n");
      wifi->Disconnect();
      continue;
    }
    while (::WiFi.isConnected()) {
      vTaskDelay(pdMS_TO_TICKS(1000));
    }
    wifi->mqtt_->Stop();
    wifi->Disconnect();
  }
}

bool network::WiFi::Start() {
  if (xTaskCreate(WiFi::WiFiTask, "wifi-task", 0x1000, this, 1, &this->wifi_task_) != pdPASS) {
    this->wifi_task_ = nullptr;
    return false;
  }
  return true;
}

void network::WiFi::Stop() {
  if (this->wifi_task_) {
    vTaskDelete(this->wifi_task_);
  }
  this->Disconnect();
}

void network::WiFi::Disconnect() {
  ::WiFi.disconnect();
  DEBUG_PRINT_PREFIX("Disconnected from WiFi\n");
}
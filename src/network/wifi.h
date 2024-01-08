#ifndef NETWORK_WIFI_H_
#define NETWORK_WIFI_H_

#include <Arduino.h>
#include <memory>
#include <string>

#include "mqtt.h"

namespace network {

class WiFi {
 public:
  WiFi(const std::string& ssid, const std::string& password,
       std::shared_ptr<Mqtt> mqtt)
      : ssid_(ssid), password_(password), mqtt_(mqtt), wifi_task_(nullptr) {}

  bool Start();
  void Stop();

 private:
  bool Connect();
  void Disconnect();

  static void WiFiTask(void* raw_wifi);

  std::string ssid_;
  std::string password_;
  std::shared_ptr<Mqtt> mqtt_;

  TaskHandle_t wifi_task_;
};

}  // namespace network

#endif  //NETWORK_WIFI_H_
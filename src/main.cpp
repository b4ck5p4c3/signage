#include <Arduino.h>
#include <memory>

#include "display/display.h"
#include "display/font.h"
#include "display/helper.h"
#include "font.h"
#include "mcu_config.h"
#include "network/mqtt.h"
#include "network/wifi.h"
#include "renderer/renderer.h"
#include "renderer/message.h"
#include "utils/debug.h"

std::shared_ptr<display::Display> main_display(
    new display::Display(DISPLAY_CLK_PIN, DISPLAY_DATA_PIN, DISPLAY_LATCH_PIN,
                         DISPLAY_ZONE_COUNT, DISPLAY_ROWS_COUNT));
std::shared_ptr<display::Font> main_font(
    new display::Font({.char_data = kCharData, .char_widths = kCharWidths}));
std::shared_ptr<renderer::Renderer> main_renderer(
    new renderer::Renderer(main_display, main_font));
std::shared_ptr<network::Mqtt> mqtt_client(new network::Mqtt(MQTT_HOST, MQTT_PORT, MQTT_CA_CERTIFICATE,
                          MQTT_USERNAME, MQTT_PASSWORD, MQTT_BASE_TOPIC, main_renderer));
std::shared_ptr<network::WiFi> wifi(new network::WiFi(WIFI_SSID, WIFI_PASSWORD, mqtt_client));

std::vector<uint8_t> StringToVector(const std::string& string) {
  return std::vector<uint8_t>(string.begin(), string.end());
}

void setup() {
  InitDebug();
  pinMode(POWER_RELAY_PIN, OUTPUT);
  digitalWrite(POWER_RELAY_PIN, LOW);

  main_display->Start(160);
  if (!main_renderer->Start()) {
    DEBUG_PRINT_PREFIX("Failed to start renderer task\n");
    ESP.restart();
    return;
  }
  main_renderer->SetBackgroundMessage(renderer::Message {
    .data = StringToVector("BKSP-signage, waiting..."),
    .brightness = 1,
    .effect_type = renderer::EffectType::SCROLL,
    .effect = {
      .scroll_effect = {
        .direction = renderer::Direction::RIGHT_TO_LEFT,
        .speed = 50
      }
    }
  });
  digitalWrite(POWER_RELAY_PIN, HIGH);
  DEBUG_PRINT_PREFIX("Display ready\n");
  if (!wifi->Start()) {
    DEBUG_PRINT_PREFIX("Failed to start WiFi task\n");
    ESP.restart();
    return;
  }
}

void loop() {}
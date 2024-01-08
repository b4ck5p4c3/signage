# signage

Firmware for B4CKSP4CE signage in openspace based on ESP32 and ~~some voodoo magic~~ shift registers

To build the project you also require to create `src/secrets.h` with defines for:
```c
#define SECRET_WIFI_PASSWORD "wifipassword" // wifi password
#define SECRET_MQTT_PASSWORD "mqttpassword" // mqtt password
```

Also probably you need to change the `WIFI_SSID` and `MQTT_*` defines in `src/mcu_config.h` for your specific environment.

If you need to add or edit protocol messages you should run setup.py in `EmbeddedProto` directory and run:
```bash
protoc --plugin=protoc-gen-eams=EmbeddedProto/protoc-gen-eams -I=src/protocol/source/ --eams_out=src/protocol/compiled/ src/protocol/source/messages.proto
```
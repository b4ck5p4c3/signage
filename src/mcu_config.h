#ifndef MCU_CONFIG_H_
#define MCU_CONFIG_H_

#include "secrets.h"

#define DEBUG_ENABLED
#define DEBUG_SERIAL Serial

#define POWER_RELAY_PIN    14

#define DISPLAY_CLK_PIN    5
#define DISPLAY_DATA_PIN   19
#define DISPLAY_LATCH_PIN  18

#define DISPLAY_ZONE_COUNT 12
#define DISPLAY_ROWS_COUNT 8
#define DISPLAY_COLS_COUNT (DISPLAY_ZONE_COUNT * 8)

#define WIFI_SSID "B4CK"
#define WIFI_PASSWORD (SECRET_WIFI_PASSWORD)

#define MQTT_HOST "mqtt.internal.0x08.in"
#define MQTT_PORT 8883
#define MQTT_CA_CERTIFICATE "-----BEGIN CERTIFICATE-----\n" \
"MIIGfzCCBGegAwIBAgIDCKqqMA0GCSqGSIb3DQEBCwUAMIHHMQswCQYDVQQGEwJS\n" \
"VTEeMBwGA1UECBMVUHJvdmluY2Ugb2YgTGVuaW5ncmFkMRcwFQYDVQQHEw5TdC4g\n" \
"UGV0ZXJzYnVyZzESMBAGA1UEChMJQjRDS1NQNENFMR0wGwYDVQQLExRTeWNoJ3Mg\n" \
"SnVpY2UgQnJld2VyeTEvMC0GA1UEAxMmQjRDS1NQNENFIFJvb3QgQ2VydGlmaWNh\n" \
"dGlvbiBBdXRob3JpdHkxGzAZBgkqhkiG9w0BCQEWDGluZm9AMHgwOC5pbjAgFw0y\n" \
"MDAxMDQxMzMzMDBaGA8yMDYyMDEwNDEzMzMwMFowgccxCzAJBgNVBAYTAlJVMR4w\n" \
"HAYDVQQIExVQcm92aW5jZSBvZiBMZW5pbmdyYWQxFzAVBgNVBAcTDlN0LiBQZXRl\n" \
"cnNidXJnMRIwEAYDVQQKEwlCNENLU1A0Q0UxHTAbBgNVBAsTFFN5Y2gncyBKdWlj\n" \
"ZSBCcmV3ZXJ5MS8wLQYDVQQDEyZCNENLU1A0Q0UgUm9vdCBDZXJ0aWZpY2F0aW9u\n" \
"IEF1dGhvcml0eTEbMBkGCSqGSIb3DQEJARYMaW5mb0AweDA4LmluMIICIjANBgkq\n" \
"hkiG9w0BAQEFAAOCAg8AMIICCgKCAgEA211QTZS2FUyZFiRmcyyCxOYijl8bJn7Q\n" \
"99dfo2wDHO8wpzx49iP66Vdv89n6/wDJUIRShfLQ3KI9C726u2rg8vZotptUo3LM\n" \
"3+agCyQoew9EjY72joykP19bmIUqlhTugTI2CcVXNZfbpmjGq4nuiZI7hxOi8AqX\n" \
"DRjOOQGaat/ihZA9MGy+0wvokfs6U8I3S6ewiWV96o7aiKHSp54UUxvcv3Hfz0nA\n" \
"uH+Tc/0kV+wjADgT0nsdvyCPjf6+EG4AwItnjlRM4zlXGgOS/ljFsrZB/0b5zbOq\n" \
"xkd96B4ZQ6Wsujf15TVeQ7mXXZqAV7DPeKqVxrSAfUhFSmgSfYJ2l+bSWbGSpjLn\n" \
"BUUBCuxJFfeJqiJZCgWb9SY+yQYcjtcyN+EUlgQuFzgOpuwPLoUEiQ1BB+1wpdF8\n" \
"XYonsxoBowJpxGHfC2i6wJVLwKOGxbLQiOkyBX0lBFzKNwm16WdB3r6Ps7nyQlTx\n" \
"gN5eZa8vFjsN6TBdPZ7QGLTlD1kqRLRaL1LZO7Sja+EyQSN1mFEv7YyxjtG5zcHy\n" \
"Vd6EFdtQPlGu3XKixy3hVQae6pgn6vAMkRQkAa3sWm4TS2NVypeAxX4v4H03MbL1\n" \
"OZ2kwXpr46tIjYeK08BTy0/znJ2+hpYCSNDvIym7PoT5M/SKW/Yd5PjmEDx4r5vh\n" \
"kchc5D4NYGECAwEAAaNwMG4wDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUkkC+\n" \
"d+WTMmicEQR9KHUjUWKWa3MwCwYDVR0PBAQDAgEGMBEGCWCGSAGG+EIBAQQEAwIA\n" \
"BzAcBglghkgBhvhCAQ0EDxYNU2FmZXR5IFRoaXJkITANBgkqhkiG9w0BAQsFAAOC\n" \
"AgEAscAWi03V9d+b7CsTDA0kd3L162vRlucbWw1XlK5F0PTJzhTvv3prmGs6ZJR5\n" \
"t7aLTm6Hv4+DM7A5+jMm9Ru79fWcS3Lwyok/v2XDOlBXE0kM9S+LQlrEGm17MM5L\n" \
"qXonjy1Y3twTLlAgf/Qj+G36DdJvt5KDZT3SeT3Jn3cjK9v0Vhx8qaoQScy7judh\n" \
"ildlZ29jUBFBhkP9shC0wZBr1DDqt+o3uXAUBZCF9tD1D7i/XqiD7f7ZR8j7q59u\n" \
"5pvYIxiZ+pPpbaLmx2UgJSTvlXasoxc5YL3EU1fvXMFD/Rdgx0GaAs6su8As8md8\n" \
"pkjgrRwToCmHOuzv7SLdGnmuhCRZFvNa5ZEYjWmCcFSzSHrFJiE9Gw/wR4uh2kVy\n" \
"EmWX2RNElhRgVGm9hkcX3bBopvfTwI4XZPQ80rfdUSwLYPCT5xxzUtDjhM0Vzz6e\n" \
"16tq6kpGD2R2w6eZRijOnb84k9oVoUt4cufNy31HO44lzXPR0yvZqsRYaNVFUYsM\n" \
"iNXU2NUx0qpnTSnYzWEyrBxAVakoJEqKm6FQMEKOAGWjWJgEy0IbhvOdJm0Xd2fY\n" \
"DwUiArlzi9oAZ1hV3y2w+Gz8HgVYve5HfizJEXjD+rWW/tIqJjD8ASs2g6lN39JZ\n" \
"jbaoSQ3ly0o/VZS8UTIo2PzKVN15/3t5Lrw3D/f+TqdoEUE=\n" \
"-----END CERTIFICATE-----\n"
#define MQTT_USERNAME "openspace-signage"
#define MQTT_PASSWORD (SECRET_MQTT_PASSWORD)
#define MQTT_BASE_TOPIC "bus/devices/openspace-signage"

#endif //MCU_CONFIG_H_
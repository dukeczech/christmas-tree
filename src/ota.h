#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

static const char* host = "esp32";
static const char* ssid = "Palmova_21a";
static const char* password = "31415926535";

void ota_setup();
void ota_loop();
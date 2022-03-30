#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "WifiService.h"

// https://github.com/witnessmenow/arduino-sample-api-request/blob/master/ESP8266/HTTP_GET/HTTP_GET.ino
WifiService::WifiService(char *hostname, char *ssid, char *password) {
  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.hostname(hostname);
  WiFi.begin(ssid, password);
  int counter = 0;
  while (WL_CONNECTED != WiFi.status()) {
    delay(500);
    Serial.print(".");
    counter++;
    if (60 < counter) {
      Serial.println();
      Serial.println(F("Failed to connect to Wifi"));
      delay(5000);
      ESP.restart();
    }
  }
}
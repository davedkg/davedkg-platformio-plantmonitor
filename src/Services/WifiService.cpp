#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "WifiService.h"

WifiService::WifiService(char *hostname, char *ssid, char *password, RGBLed *led) {
  _led = led;
  _led->blue();
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
      _led->red();
      Serial.println();
      Serial.println(F("Failed to connect to Wifi"));
      delay(5000);
      ESP.restart();
    }
  }
  _led->green();
}
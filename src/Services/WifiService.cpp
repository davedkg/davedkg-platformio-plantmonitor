#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "WifiService.h"

WifiService::WifiService(char *hostname, char *ssid, char *password) {
  _hostname = hostname;
  _ssid = ssid;
  _password = password;

  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.hostname(_hostname);
}

bool WifiService::connect() {
  if (WL_CONNECTED == WiFi.status()) {
    return true;
  }

  WiFi.begin(_ssid, _password);
  int counter = 0;
  Serial.print("connecting to wifi");

  while (WL_CONNECTED != WiFi.status()) {
    Serial.print(".");
    counter++;
    if (20 < counter) {
      Serial.println();
      Serial.println(F("failed to connect to wifi!"));
      return false;
    }
    delay(1000);
  }

  Serial.println();
  Serial.println("connected to wifi");

  return true;
}

bool WifiService::disconnect() {
  Serial.println("disconnecting from wifi");
  WiFi.disconnect(true);
  Serial.println("disconnected from wifi");
}
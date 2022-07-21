#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "WifiService.h"

WifiService::WifiService(char *hostname, char *ssid, char *password, Logger *logger) {
  _hostname = hostname;
  _ssid = ssid;
  _password = password;
  _logger = logger;

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
  _logger->print("connecting to wifi");

  while (WL_CONNECTED != WiFi.status()) {
    _logger->print(".");
    counter++;
    if (20 < counter) {
      _logger->println("");
      _logger->println(F("failed to connect to wifi!"));
      return false;
    }
    delay(1000);
  }

  _logger->println("");
  _logger->println("connected to wifi");

  return true;
}

bool WifiService::disconnect() {
  _logger->println("disconnecting from wifi");
  WiFi.disconnect(true);
  _logger->println("disconnected from wifi");
}
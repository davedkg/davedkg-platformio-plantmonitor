#include <Arduino.h>
#include <WiFiClientSecure.h>
#include "RemoteStorageService.h"

WiFiClientSecure client;

// https://github.com/witnessmenow/arduino-sample-api-request/blob/master/ESP8266/HTTP_GET/HTTP_GET.ino
RemoteStorageService::RemoteStorageService(char *apiKey, char *domain, RGBLed *led) {
  _apiKey = apiKey;
  _domain = domain;
  _led = led;

  client.setInsecure();

  if (false == ping()) {
    int counter = 0;

    while (true) {
      led->red();
      delay(500);
      led->off();
      delay(500);
      counter++;
      if (10 == counter) {
        ESP.restart();
      }
    }
  }
}

bool RemoteStorageService::ping() {
  if (!client.connect(_domain, 443)) {
    Serial.println(F("Unable to open connection"));
    return false;
  }

  yield();

  client.print(F("GET "));
  client.print("/api/ping");
  client.println(F(" HTTP/1.1"));
  client.print(F("Host: "));
  client.println(_domain);
  client.println(F("Cache-Control: no-cache"));

  if (0 == client.println()) {
    Serial.println(F("Failed to send request"));
    return false;
  }

  char status[32] = {0};
  client.readBytesUntil('\r', status, sizeof(status));
  if (0 != strcmp(status, "HTTP/1.1 200 OK")) {
    Serial.print(F("Unexpected response: "));
    Serial.println(status);
    return false;
  }

  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders)) {
    Serial.println(F("Invalid response"));
    return false;
  }

  while (client.available()) {
    char c = 0;
    client.readBytes(&c, 1);
    Serial.print(c);
  }

  return true;
}
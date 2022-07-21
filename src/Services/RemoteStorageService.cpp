#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "RemoteStorageService.h"

RemoteStorageService::RemoteStorageService(String domain, Logger *logger) {
  _domain = domain;
  _logger = logger;
}

bool RemoteStorageService::saveReading(String apiKey, float moisture, float temperature, float humidity, bool raining, float lightIntensity) {
  _logger->println(F("saving reading to api"));

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String params = "api_key=" + apiKey;
    params += "&plant_reading[soil_moisture]=" + String(moisture);
    params += "&plant_reading[humidity]=" + String(humidity);
    params += "&plant_reading[temperature]=" + String(temperature);
    params += "&plant_reading[light_intensity]=" + String(lightIntensity);
    params += "&plant_reading[raining]=";
    if (raining) {
      params += "true";
    } else {
      params += "false";
    }
    _logger->println(params);

    http.begin("http://" + _domain + "/plant-readings");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpCode = http.POST(params);

    _logger->println("save reading returned code: " + String(httpCode));

    if (204 != httpCode) {
      String payload = http.getString();
      _logger->println(payload);
      http.end();

      return false;
    }

    http.end();
  } else {
    _logger->println(F("unable to save reading to api because not connected to wifi!"));

    return false;
  }

  _logger->println(F("saved reading to api"));

  return true;
}

bool RemoteStorageService::ping() {
  _logger->println(F("pinging api"));

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin("http://" + _domain + "/ping");
    int httpCode = http.GET();

    _logger->println("ping returned code: " + String(httpCode));

    if (204 != httpCode) {
      String payload = http.getString();
      _logger->println(payload);
      http.end();

      return false;
    }

    http.end();
    _logger->println(F("pinged api"));

    return true;
  } else {
    _logger->println(F("unable to ping api because not connected to wifi!"));

    return false;
  }
}
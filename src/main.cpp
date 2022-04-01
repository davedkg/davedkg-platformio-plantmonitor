#include <Arduino.h>

#include "Credentials.h"
#include "Outputs/Display.h"
#include "Sensors/AtmosphereSensor.h"
#include "Services/RemoteStorageService.h"
#include "Services/WifiService.h"

#define THREE_SECONDS 3000
#define FIVE_SECONDS 5000
#define ATMOSPHERE_SENSOR_PIN D5

AtmosphereSensor *atmosphereSensor;
Display *display;
RemoteStorageService *remoteStorageService;
WifiService *wifiService;

float atmosphereTemperature = 0.0;
float atmosphereHumidity = 0.0;
float soilMoisture1 = 0.0;
float soilMoisture2 = 0.0;
float lightIntensity = 0.0;
bool raining = false;

void setup() {
  Serial.begin(115200);

  display = new Display();
  atmosphereSensor = new AtmosphereSensor(ATMOSPHERE_SENSOR_PIN);

  display->drawSplash(connecting, unknown);
  wifiService = new WifiService(WIFI_DEVICE_NAME, WIFI_SSID, WIFI_PASSWORD);
  if (false == wifiService->connect()) {
    display->drawSplash(failed, unknown);
    delay(FIVE_SECONDS);
    ESP.restart();
  }

  display->drawSplash(connected, connecting);
  remoteStorageService = new RemoteStorageService(API_DOMAIN);
  if (false == remoteStorageService->ping()) {
    display->drawSplash(connected, failed);
    delay(FIVE_SECONDS);
    ESP.restart();
  }

  display->drawSplash(connected, connected);
  delay(THREE_SECONDS);
}

void updateReadings() {
  atmosphereTemperature = atmosphereSensor->temperature();
  atmosphereHumidity = atmosphereSensor->humidity();
  soilMoisture1 = 0.0;
  soilMoisture2 = 0.0;
  lightIntensity = 0.0;
  raining = false;
}

void loop() {
  updateReadings();
  display->drawReadings(atmosphereTemperature, atmosphereHumidity, soilMoisture1, soilMoisture2, lightIntensity, raining);
  // TODO save readings every 15 minutes
  delay(5000);
}
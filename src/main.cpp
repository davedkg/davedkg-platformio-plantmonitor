#include <Arduino.h>
#include "Credentials.h"
#include "Outputs/Display.h"
#include "Outputs/RGBLed.h"
#include "Sensors/AtmosphereSensor.h"
#include "Sensors/SoilSensor.h"

#define WET_SOIL_MOISTURE_CAPACITANCE 1265
#define DRY_SOIL_MOISTURE_CAPACITANCE 2970

AtmosphereSensor *atmosphereSensor;
Display *display;
RGBLed *led;
SoilSensor *soilSensor;

// ** WiFi
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

void setupWifi() {
  led->blue();
  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.hostname(WIFI_DEVICE_NAME);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  int counter = 0;
  while (WL_CONNECTED != WiFi.status()) {
    delay(500);
    Serial.print(".");
    counter++;
    if (60 < counter) {
      led->red();
      Serial.println();
      Serial.println(F("Failed to connect to Wifi"));
      delay(5000);
      ESP.restart();
    }
  }
  led->green();
}

void setup() {
  Serial.begin(115200);

  atmosphereSensor = new AtmosphereSensor(D5);
  display = new Display();
  led = new RGBLed(D3, D4, D7);
  soilSensor = new SoilSensor(D6, WET_SOIL_MOISTURE_CAPACITANCE, DRY_SOIL_MOISTURE_CAPACITANCE);

  display->splash();
  setupWifi();

  delay(2000); // View Startup state on Outputs
  led->off();
}

void loop() {
  int soilMoisture = soilSensor->moisture();
  float atmosphereTemperature = atmosphereSensor->temperature();
  float atmosphereHumidity = atmosphereSensor->humidity();

  display->update(soilMoisture, atmosphereTemperature, atmosphereHumidity);

  delay(5000);
}
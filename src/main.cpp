#include <Arduino.h>
#include "Credentials.h"
#include "Outputs/Display.h"
#include "Outputs/RGBLed.h"
#include "Outputs/WebService.h"
#include "Sensors/AtmosphereSensor.h"
#include "Sensors/SoilSensor.h"

#define WET_SOIL_MOISTURE_CAPACITANCE 1265
#define DRY_SOIL_MOISTURE_CAPACITANCE 2970

AtmosphereSensor *atmosphereSensor;
Display *display;
RGBLed *led;
SoilSensor *soilSensor;
WebService *webService;

void setup() {
  Serial.begin(115200);

  display = new Display();
  display->splash(true);

  led = new RGBLed(D3, D4, D7);
  webService = new WebService(WIFI_DEVICE_NAME, WIFI_SSID, WIFI_PASSWORD, led);
  display->splash(false);

  atmosphereSensor = new AtmosphereSensor(D5);
  soilSensor = new SoilSensor(D6, WET_SOIL_MOISTURE_CAPACITANCE, DRY_SOIL_MOISTURE_CAPACITANCE);

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
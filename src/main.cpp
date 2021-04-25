#include <Arduino.h>
#include "Credentials.h"
#include "Outputs/Display.h"
#include "Outputs/RGBLed.h"
#include "Sensors/AtmosphereSensor.h"
#include "Sensors/SoilSensor.h"
#include "Services/WifiService.h"

#define RED_LED_PIN D3 // digital
#define GREEN_LED_PIN D4 // digital
#define BLUE_LED_PIN D7 // digital
#define ATMOSPHERE_SENSOR_PIN D5 // analog
#define SOIL_SENSOR_PIN D6 // analog

// calibrate you soil sensor when its dry and submerged in water
#define WET_SOIL_MOISTURE_CAPACITANCE 1265
#define DRY_SOIL_MOISTURE_CAPACITANCE 2970

AtmosphereSensor *atmosphereSensor;
Display *display;
RGBLed *led;
SoilSensor *soilSensor;
WifiService *wifiService;

void setup() {
  Serial.begin(115200);

  display = new Display();
  display->splash(true);

  led = new RGBLed(RED_LED_PIN, GREEN_LED_PIN, BLUE_LED_PIN);
  wifiService = new WifiService(WIFI_DEVICE_NAME, WIFI_SSID, WIFI_PASSWORD, led);
  display->splash(false);

  atmosphereSensor = new AtmosphereSensor(ATMOSPHERE_SENSOR_PIN);
  soilSensor = new SoilSensor(SOIL_SENSOR_PIN, WET_SOIL_MOISTURE_CAPACITANCE, DRY_SOIL_MOISTURE_CAPACITANCE);

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
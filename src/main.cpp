#include <Arduino.h>
#include "Credentials.h"
#include "Outputs/Display.h"
#include "Outputs/RGBLed.h"
#include "Sensors/AtmosphereSensor.h"
#include "Sensors/SoilSensor.h"
#include "Sensors/RaindropSensor.h"
#include "Services/RemoteStorageService.h"
#include "Services/WifiService.h"

#define RED_LED_PIN D3 // digital
#define GREEN_LED_PIN D4 // digital
#define BLUE_LED_PIN D7 // digital
#define ATMOSPHERE_SENSOR_PIN D5 // analog
#define SOIL_SENSOR_PIN D6 // analog
#define RAINDROP_SENSOR_PIN A0 // analog

// calibrate you soil sensor when its dry and submerged in water
#define WET_SOIL_MOISTURE_CAPACITANCE 1265
#define DRY_SOIL_MOISTURE_CAPACITANCE 2970

AtmosphereSensor *atmosphereSensor;
Display *display;
RGBLed *led;
SoilSensor *soilSensor;
RaindropSensor *raindropSensor;
RemoteStorageService *remoteStorageService;
WifiService *wifiService;

void setup() {
  Serial.begin(115200);

  display = new Display();
  display->splash(true, true);

  led = new RGBLed(RED_LED_PIN, GREEN_LED_PIN, BLUE_LED_PIN);
  atmosphereSensor = new AtmosphereSensor(ATMOSPHERE_SENSOR_PIN);
  soilSensor = new SoilSensor(SOIL_SENSOR_PIN, WET_SOIL_MOISTURE_CAPACITANCE, DRY_SOIL_MOISTURE_CAPACITANCE);
  raindropSensor = new RaindropSensor(RAINDROP_SENSOR_PIN);

  led->red();

  wifiService = new WifiService(WIFI_DEVICE_NAME, WIFI_SSID, WIFI_PASSWORD);
  display->splash(false, true);
  led->blue();

  remoteStorageService = new RemoteStorageService(API_DOMAIN);
  display->splash(false, false);
  led->green();

  delay(5000); // View Startup state on Outputs
  led->off();
}

void loop() {
  int moisture = soilSensor->moisture();
  float temperature = atmosphereSensor->temperature();
  float humidity = atmosphereSensor->humidity();
  bool raining = raindropSensor->raining();

  display->update(moisture, temperature, humidity, raining);
  // remoteStorageService->saveReading("TODO", moisture, temperature, humidity, raining);

  delay(5000);
}
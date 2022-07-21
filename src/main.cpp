#include <Arduino.h>
#include <Adafruit_ADS1X15.h>

#include "Credentials.h"
#include "Calibrations.h"
#include "Outputs/Logger.h"
#include "Sensors/AtmosphereSensor.h"
#include "Sensors/LightSensor.h"
#include "Sensors/RainSensor.h"
#include "Sensors/SoilSensor.h"
#include "Services/RemoteStorageService.h"
#include "Services/WifiService.h"

#define ONE_SECOND 1000
#define DISPLAY_READINGS_COUNTDOWN_SECONDS 30
#define SAVE_READINGS_COUNTDOWN_SECONDS 60 * 15
#define LIGHT_SENSOR_PIN 0
#define SOIL_SENSOR_1_PIN 1
#define SOIL_SENSOR_2_PIN 2
#define RAIN_SENSOR_PIN 3
#define ATMOSPHERE_SENSOR_PIN D4
#define LOGGER_PIN D8

AtmosphereSensor *atmosphereSensor;
LightSensor *lightSensor;
RainSensor *rainSensor;
SoilSensor *soilSensor1;
SoilSensor *soilSensor2;
RemoteStorageService *remoteStorageService;
WifiService *wifiService;
Adafruit_ADS1015 ads1015;
Logger *logger;

void setup() {
  Serial.begin(115200);
  // ads1015.begin();

  logger = new Logger(LOGGER_PIN);
  // atmosphereSensor = new AtmosphereSensor(ATMOSPHERE_SENSOR_PIN);
  // lightSensor = new LightSensor(ads1015, LIGHT_SENSOR_PIN);
  // rainSensor = new RainSensor(ads1015, RAIN_SENSOR_PIN, RAIN_SENSOR_THRESHOLD);
  // soilSensor1 = new SoilSensor(ads1015, SOIL_SENSOR_1_PIN, SOIL_SENSOR_1_MIN_THRESHOLD, SOIL_SENSOR_1_MAX_THRESHOLD);
  // soilSensor2 = new SoilSensor(ads1015, SOIL_SENSOR_2_PIN, SOIL_SENSOR_2_MIN_THRESHOLD, SOIL_SENSOR_2_MAX_THRESHOLD);

  // wifiService = new WifiService(WIFI_DEVICE_NAME, WIFI_SSID, WIFI_PASSWORD, logger);
  // if (false == wifiService->connect()) {
  //   delay(ONE_SECOND * 5);
  //   ESP.restart();
  // }

  // remoteStorageService = new RemoteStorageService(API_DOMAIN, logger);
  // if (false == remoteStorageService->ping()) {
  //   delay(ONE_SECOND * 5);
  //   ESP.restart();
  // }
}

// void saveReadings() {
//   wifiService->connect();

//   float atmosphereTemperature = 0;//atmosphereSensor->temperature();
//   float atmosphereHumidity = 0;//atmosphereSensor->humidity();
//   float soilMoisture1 = soilSensor1->moisture();
//   float soilMoisture2 = soilSensor2->moisture();
//   float lightIntensity = lightSensor->intensity();
//   bool raining = rainSensor->raining();

//   remoteStorageService->saveReading(PLANT_1_API_KEY, soilMoisture1, atmosphereTemperature, atmosphereHumidity, raining, lightIntensity);
//   remoteStorageService->saveReading(PLANT_2_API_KEY, soilMoisture2, atmosphereTemperature, atmosphereHumidity, raining, lightIntensity);

//   wifiService->disconnect();
// }

void loop() {
  logger->println("writing to log");
  delay(ONE_SECOND);
}
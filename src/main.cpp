#include <Arduino.h>
#include <Adafruit_ADS1X15.h>

#include "Credentials.h"
#include "Calibrations.h"
#include "Outputs/Display.h"
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
#define ATMOSPHERE_SENSOR_PIN D7
#define BUTTON_PIN D4

AtmosphereSensor *atmosphereSensor;
LightSensor *lightSensor;
RainSensor *rainSensor;
SoilSensor *soilSensor1;
SoilSensor *soilSensor2;
Display *display;
RemoteStorageService *remoteStorageService;
WifiService *wifiService;
Adafruit_ADS1015 ads1015;
int displayReadingsCountdownSeconds;
int saveReadingsCountdownSeconds;

void setup() {
  Serial.begin(115200);
  ads1015.begin();
  pinMode(BUTTON_PIN, INPUT);
  displayReadingsCountdownSeconds = DISPLAY_READINGS_COUNTDOWN_SECONDS;
  saveReadingsCountdownSeconds = 5; // give the sensors time to warm up

  atmosphereSensor = new AtmosphereSensor(ATMOSPHERE_SENSOR_PIN);
  lightSensor = new LightSensor(ads1015, LIGHT_SENSOR_PIN);
  rainSensor = new RainSensor(ads1015, RAIN_SENSOR_PIN, RAIN_SENSOR_THRESHOLD);
  soilSensor1 = new SoilSensor(ads1015, SOIL_SENSOR_1_PIN, SOIL_SENSOR_1_MIN_THRESHOLD, SOIL_SENSOR_1_MAX_THRESHOLD);
  soilSensor2 = new SoilSensor(ads1015, SOIL_SENSOR_2_PIN, SOIL_SENSOR_2_MIN_THRESHOLD, SOIL_SENSOR_2_MAX_THRESHOLD);
  display = new Display();

  display->drawSplash(connecting, unknown);
  wifiService = new WifiService(WIFI_DEVICE_NAME, WIFI_SSID, WIFI_PASSWORD);
  if (false == wifiService->connect()) {
    display->drawSplash(failed, unknown);
    delay(ONE_SECOND * 5);
    ESP.restart();
  }

  display->drawSplash(connected, connecting);
  remoteStorageService = new RemoteStorageService(API_DOMAIN);
  if (false == remoteStorageService->ping()) {
    display->drawSplash(connected, failed);
    delay(ONE_SECOND * 5);
    ESP.restart();
  }

  display->drawSplash(connected, connected);
  delay(ONE_SECOND * 3);
}

void saveReadings() {
  wifiService->connect();

  float atmosphereTemperature = atmosphereSensor->temperature();
  float atmosphereHumidity = atmosphereSensor->humidity();
  float soilMoisture1 = soilSensor1->moisture();
  float soilMoisture2 = soilSensor2->moisture();
  float lightIntensity = lightSensor->intensity();
  bool raining = rainSensor->raining();

  remoteStorageService->saveReading(PLANT_1_API_KEY, soilMoisture1, atmosphereTemperature, atmosphereHumidity, raining, lightIntensity);
  remoteStorageService->saveReading(PLANT_2_API_KEY, soilMoisture2, atmosphereTemperature, atmosphereHumidity, raining, lightIntensity);

  wifiService->disconnect();
}

void displayReadings() {
  float atmosphereTemperature = atmosphereSensor->temperature();
  float atmosphereHumidity = atmosphereSensor->humidity();
  float soilMoisture1 = soilSensor1->moisture();
  float soilMoisture2 = soilSensor2->moisture();
  float lightIntensity = lightSensor->intensity();
  bool raining = rainSensor->raining();

  display->drawReadings(atmosphereTemperature, atmosphereHumidity, soilMoisture1, soilMoisture2, lightIntensity, raining);
}

void displayCalibrations() {
  int16_t rainInput  = rainSensor->rawValue();
  int16_t lightInput = lightSensor->rawValue();
  int16_t soilInput1 = soilSensor1->rawValue();
  int16_t soilInput2 = soilSensor2->rawValue();

  display->drawCalibrations(lightInput, rainInput, soilInput1, soilInput2);
}

void loop() {
  if (CALIBRATION_MODE) {
    displayCalibrations();
    delay(ONE_SECOND);
  } else {
    if (HIGH == digitalRead(BUTTON_PIN)) {
      displayReadingsCountdownSeconds = DISPLAY_READINGS_COUNTDOWN_SECONDS;
    }

    if (0 < displayReadingsCountdownSeconds) {
      displayReadings();
      displayReadingsCountdownSeconds--;
    } else {
      display->turnOff();
    }

    if (0 == saveReadingsCountdownSeconds) {
      saveReadings();
      saveReadingsCountdownSeconds = SAVE_READINGS_COUNTDOWN_SECONDS;
    } else {
      saveReadingsCountdownSeconds--;
    }

    delay(ONE_SECOND);
  }
}
#include <Arduino.h>
#include <Adafruit_ADS1X15.h>

#include "Credentials.h"
#include "Calibrations.h"
#include "Outputs/Display.h"
#include "Sensors/AtmosphereSensor.h"
#include "Services/RemoteStorageService.h"
#include "Services/WifiService.h"

#define ONE_SECOND 1000
#define THREE_SECONDS 3000
#define FIVE_SECONDS 5000
#define ATMOSPHERE_SENSOR_PIN D7

int16_t MAX_ANALOG_THRESHOLD = 2047.0;

AtmosphereSensor *atmosphereSensor;
Display *display;
RemoteStorageService *remoteStorageService;
WifiService *wifiService;
Adafruit_ADS1015 ads1015;

void setup() {
  Serial.begin(115200);

  ads1015.begin();

  atmosphereSensor = new AtmosphereSensor(ATMOSPHERE_SENSOR_PIN);
  display = new Display();

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
  int16_t adc0 = ads1015.readADC_SingleEnded(0); // Rain Sensor
  int16_t adc1 = ads1015.readADC_SingleEnded(1); // Light Sensor
  int16_t adc2 = ads1015.readADC_SingleEnded(2); // Soil Sensor 1
  int16_t adc3 = ads1015.readADC_SingleEnded(3); // Soil Sensor 2

  float atmosphereTemperature = atmosphereSensor->temperature();
  float atmosphereHumidity = atmosphereSensor->humidity();
  float soilMoisture1 = 100.0f - (((float)adc2 - SOIL_SENSOR_1_MIN_THRESHOLD) / (SOIL_SENSOR_1_MAX_THRESHOLD - SOIL_SENSOR_1_MIN_THRESHOLD) * 100.0f);
  float soilMoisture2 = 100.0f - (((float)adc3 - SOIL_SENSOR_2_MIN_THRESHOLD) / (SOIL_SENSOR_2_MAX_THRESHOLD - SOIL_SENSOR_2_MIN_THRESHOLD) * 100.0f);
  float lightIntensity = ((float)adc1 / 2047.0f) * 100.0f;
  bool raining = (float)adc0 < RAIN_SENSOR_THRESHOLD;

  display->drawReadings(atmosphereTemperature, atmosphereHumidity, soilMoisture1, soilMoisture2, lightIntensity, raining);
  remoteStorageService->saveReading(PLANT_1_API_KEY, soilMoisture1, atmosphereTemperature, atmosphereHumidity, raining, lightIntensity);
  remoteStorageService->saveReading(PLANT_2_API_KEY, soilMoisture2, atmosphereTemperature, atmosphereHumidity, raining, lightIntensity);

  delay(FIVE_SECONDS);
}

void calebrateSensors() {
  int16_t adc0, adc1, adc2, adc3;

  adc0 = ads1015.readADC_SingleEnded(0); // Rain Sensor
  adc1 = ads1015.readADC_SingleEnded(1); // Light Sensor
  adc2 = ads1015.readADC_SingleEnded(2); // Soil Sensor 1
  adc3 = ads1015.readADC_SingleEnded(3); // Soil Sensor 2

  display->drawCalibrations(adc1, adc0, adc2, adc3);

  delay(ONE_SECOND);
}

void loop() {
  // calebrateSensors();
  updateReadings();
}
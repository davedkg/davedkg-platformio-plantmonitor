#include "SoilSensor.h"

SoilSensor::SoilSensor(Adafruit_ADS1015 ads1015, int pin, float minThreshold, float maxThreshold) {
  _ads1015 = ads1015;
  _pin = pin;
  _minThreshold = minThreshold;
  _maxThreshold = maxThreshold;
}

float SoilSensor::moisture() {
  return 100.0f - (((float)rawValue() - _minThreshold) / (_maxThreshold - _minThreshold) * 100.0f);
}

int16_t SoilSensor::rawValue() {
  return _ads1015.readADC_SingleEnded(_pin);
}
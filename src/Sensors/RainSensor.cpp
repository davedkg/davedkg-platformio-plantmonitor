#include "RainSensor.h"

RainSensor::RainSensor(Adafruit_ADS1015 ads1015, int pin, float threshold) {
  _ads1015 = ads1015;
  _pin = pin;
  _threshold = threshold;
}

bool RainSensor::raining() {
  return (float)rawValue() < _threshold;
}

int16_t RainSensor::rawValue() {
  return _ads1015.readADC_SingleEnded(_pin);
}
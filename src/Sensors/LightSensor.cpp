#include "LightSensor.h"

int16_t MAX_ANALOG_THRESHOLD = 2047.0f;

LightSensor::LightSensor(Adafruit_ADS1015 ads1015, int pin) {
  _ads1015 = ads1015;
  _pin = pin;
}

float LightSensor::intensity() {
  return ((float)rawValue() / MAX_ANALOG_THRESHOLD) * 100.0f;
}

int16_t LightSensor::rawValue() {
  return _ads1015.readADC_SingleEnded(_pin);
}
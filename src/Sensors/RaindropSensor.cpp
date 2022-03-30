#include <Arduino.h>
#include "RaindropSensor.h"

RaindropSensor::RaindropSensor(int pin) {
  pinMode(pin, INPUT);
  _pin = pin;
}

bool RaindropSensor::raining() {
  return analogRead(_pin) < 1000;
}
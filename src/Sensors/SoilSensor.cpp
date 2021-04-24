#include <Arduino.h>
#include "SoilSensor.h"

SoilSensor::SoilSensor(int pin, int wetSoilMoistureCapacitance, int drySoilMoistureCapacitance) {
  pinMode(pin, INPUT);
  _pin = pin;
  _wetSoilMoistureCapacitance = wetSoilMoistureCapacitance;
  _drySoilMoistureCapacitance = drySoilMoistureCapacitance;
}

int SoilSensor::moisture() {
  return map(analogRead(_pin), _wetSoilMoistureCapacitance, _drySoilMoistureCapacitance, 100, 0);
}
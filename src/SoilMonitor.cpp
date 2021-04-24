#include <Arduino.h>
#include "SoilMonitor.h"

SoilMonitor::SoilMonitor(int pin, int wetSoilMoistureCapacitance, int drySoilMoistureCapacitance) {
  pinMode(pin, INPUT);
  _pin = pin;
  _wetSoilMoistureCapacitance = wetSoilMoistureCapacitance;
  _drySoilMoistureCapacitance = drySoilMoistureCapacitance;
}

int SoilMonitor::moisture() {
  return map(analogRead(_pin), _wetSoilMoistureCapacitance, _drySoilMoistureCapacitance, 100, 0);
}
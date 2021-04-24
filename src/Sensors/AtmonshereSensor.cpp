#include <Arduino.h>
#include <DHT.h>
#include <DHT_U.h>
#include "AtmosphereSensor.h"

DHT_Unified* _atmosphereSensor;

AtmosphereSensor::AtmosphereSensor(int pin) {
  _atmosphereSensor = new DHT_Unified(pin, DHT22);
  _atmosphereSensor->begin();
}

float AtmosphereSensor::temperature() {
  sensors_event_t event;
  _atmosphereSensor->temperature().getEvent(&event);

  return event.temperature;
}

float AtmosphereSensor::humidity() {
  sensors_event_t event;
  _atmosphereSensor->humidity().getEvent(&event);

  return event.relative_humidity;
}
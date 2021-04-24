#ifndef AtmosphereSensor_h
#define AtmosphereSensor_h

#include <Arduino.h>

class AtmosphereSensor
{
  public:
    AtmosphereSensor(int pin);
    float temperature();
    float humidity();
};

#endif
#ifndef RaindropSensor_h
#define RaindropSensor_h

#include <Arduino.h>

class RaindropSensor
{
  public:
    RaindropSensor(int pin);
    bool raining();
  private:
    int _pin;
};

#endif
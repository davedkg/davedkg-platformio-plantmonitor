#ifndef SoilSensor_h
#define SoilSensor_h

#include <Arduino.h>

class SoilSensor
{
  public:
    SoilSensor(int pin, int wetSoilMoistureCapacitance, int drySoilMoistureCapacitance);
    int moisture();
  private:
    int _pin;
    int _wetSoilMoistureCapacitance;
    int _drySoilMoistureCapacitance;
};

#endif
#ifndef SoilMonitor_h
#define SoilMonitor_h

#include <Arduino.h>

class SoilMonitor
{
  public:
    SoilMonitor(int pin, int wetSoilMoistureCapacitance, int drySoilMoistureCapacitance);
    int moisture();
  private:
    int _pin;
    int _wetSoilMoistureCapacitance;
    int _drySoilMoistureCapacitance;
};

#endif
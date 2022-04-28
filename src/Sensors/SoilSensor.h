#ifndef SoilSensor_h
#define SoilSensor_h

#include <Arduino.h>
#include <Adafruit_ADS1X15.h>

class SoilSensor
{
  public:
    SoilSensor(Adafruit_ADS1015 ads1015, int pin, float minThreshold, float maxThreshold);
    float moisture();
    int16_t rawValue();

  private:
    Adafruit_ADS1015 _ads1015;
    int _pin;
    int _minThreshold;
    int _maxThreshold;
};

#endif
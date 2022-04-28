#ifndef LightSensor_h
#define LightSensor_h

#include <Arduino.h>
#include <Adafruit_ADS1X15.h>

class LightSensor
{
  public:
    LightSensor(Adafruit_ADS1015 ads1015, int pin);
    float intensity();
    int16_t rawValue();

  private:
    Adafruit_ADS1015 _ads1015;
    int _pin;
};

#endif
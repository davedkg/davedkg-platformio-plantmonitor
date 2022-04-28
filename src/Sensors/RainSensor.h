#ifndef RainSensor_h
#define RainSensor_h

#include <Arduino.h>
#include <Adafruit_ADS1X15.h>

class RainSensor
{
  public:
    RainSensor(Adafruit_ADS1015 ads1015, int pin, float threshold);
    bool raining();
    int16_t rawValue();

  private:
    Adafruit_ADS1015 _ads1015;
    int _pin;
    float _threshold;
};

#endif
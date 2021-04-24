#ifndef RGBLed_h
#define RGBLed_h

#include <Arduino.h>

class RGBLed
{
  public:
    RGBLed(int redPin, int greenPin, int bluePin);
    void off();
    void red();
    void green();
    void blue();
  private:
    int _redPin;
    int _greenPin;
    int _bluePin;
};

#endif
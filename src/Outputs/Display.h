#ifndef Display_h
#define Display_h

#include <Arduino.h>

class Display
{
  public:
    Display();
    void splash(bool connecting);
    void update(int soilMoisture, float temperature, float humidity);
};

#endif
#ifndef WebService_h
#define WebService_h

#include <Arduino.h>
#include "Outputs/RGBLed.h"

class WebService
{
  public:
    WebService(char *hostname, char *ssid, char *password, RGBLed *led);
  private:
    RGBLed *_led;
};

#endif
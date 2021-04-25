#ifndef WifiService_h
#define WifiService_h

#include <Arduino.h>
#include "Outputs/RGBLed.h"

class WifiService
{
  public:
    WifiService(char *hostname, char *ssid, char *password, RGBLed *led);
  private:
    RGBLed *_led;
};

#endif
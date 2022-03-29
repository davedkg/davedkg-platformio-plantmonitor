#ifndef RemoteStorageService_h
#define RemoteStorageService_h

#include <Arduino.h>
#include "Outputs/RGBLed.h"

class RemoteStorageService
{
  public:
    RemoteStorageService(char *domain, RGBLed *led);
    bool ping();
    bool saveReading(char *apiKey, int moisture, float temperature, float humidity);
  private:
    char *_domain;
    bool _ssl;
    RGBLed *_led;
};

#endif
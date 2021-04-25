#ifndef RemoteStorageService_h
#define RemoteStorageService_h

#include <Arduino.h>
#include "Outputs/RGBLed.h"

class RemoteStorageService
{
  public:
    RemoteStorageService(char *apiKey, char *domain, RGBLed *led);
    bool ping();
  private:
    char *_apiKey;
    char *_domain;
    bool _ssl;
    RGBLed *_led;
};

#endif
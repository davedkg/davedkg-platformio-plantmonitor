#ifndef WifiService_h
#define WifiService_h

#include <Arduino.h>

class WifiService
{
  public:
    WifiService(char *hostname, char *ssid, char *password);
};

#endif
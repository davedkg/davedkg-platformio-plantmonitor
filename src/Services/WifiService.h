#ifndef WifiService_h
#define WifiService_h

#include <Arduino.h>
#include "Outputs/Logger.h"

class WifiService
{
  public:
    WifiService(char *hostname, char *ssid, char *password, Logger *logger);
    bool connect();
    bool disconnect();
  private:
    char *_hostname;
    char *_ssid;
    char *_password;
    Logger *_logger;
};

#endif
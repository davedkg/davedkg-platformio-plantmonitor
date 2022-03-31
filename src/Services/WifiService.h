#ifndef WifiService_h
#define WifiService_h

#include <Arduino.h>

class WifiService
{
  public:
    WifiService(char *hostname, char *ssid, char *password);
    bool connect();
    bool disconnect();
  private:
    char *_hostname;
    char *_ssid;
    char *_password;
};

#endif
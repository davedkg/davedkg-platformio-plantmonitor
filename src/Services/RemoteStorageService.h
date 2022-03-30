#ifndef RemoteStorageService_h
#define RemoteStorageService_h

#include <Arduino.h>

class RemoteStorageService
{
  public:
    RemoteStorageService(char *domain);
    bool ping();
    bool saveReading(char *apiKey, int moisture, float temperature, float humidity);
  private:
    char *_domain;
    bool _ssl;
};

#endif
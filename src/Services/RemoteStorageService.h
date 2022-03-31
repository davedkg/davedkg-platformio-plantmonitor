#ifndef RemoteStorageService_h
#define RemoteStorageService_h

#include <Arduino.h>

class RemoteStorageService
{
  public:
    RemoteStorageService(String domain);
    bool ping();
    bool saveReading(String apiKey, int moisture, float temperature, float humidity, bool raining);
  private:
    String _domain;
};

#endif
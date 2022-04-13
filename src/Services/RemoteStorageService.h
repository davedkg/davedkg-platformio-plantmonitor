#ifndef RemoteStorageService_h
#define RemoteStorageService_h

#include <Arduino.h>

class RemoteStorageService
{
  public:
    RemoteStorageService(String domain);
    bool ping();
    // FIXME standardize variable names
    bool saveReading(String apiKey, int moisture, float temperature, float humidity, bool raining, float lightIntensity);
  private:
    String _domain;
};

#endif
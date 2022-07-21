#ifndef RemoteStorageService_h
#define RemoteStorageService_h

#include <Arduino.h>
#include "Outputs/Logger.h"

class RemoteStorageService
{
  public:
    RemoteStorageService(String domain, Logger *logger);
    bool ping();
    // FIXME standardize variable names
    bool saveReading(String apiKey, float moisture, float temperature, float humidity, bool raining, float lightIntensity);
  private:
    String _domain;
    Logger *_logger;
};

#endif
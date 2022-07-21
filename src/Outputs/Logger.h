#ifndef Logger_h
#define Logger_h

#include <Arduino.h>

class Logger
{
  public:
    Logger(int pin);
    void print(String text);
    void println(String text);
};

#endif
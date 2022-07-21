#include "Logger.h"
#include "SPI.h"
#include "SD.h"

#define LOG_FILE "log.txt"

Logger::Logger(int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);

  if (!SD.begin(pin)) {
    Serial.println("Failed to initialize logger");
  }
}

void Logger::print(String text) {
  Serial.print(text);

  File logFile = SD.open(LOG_FILE, FILE_WRITE);
  if (logFile) {
    logFile.print(text);
    logFile.close();
  } else {
    Serial.println("Unable to write to log");
  }
}

void Logger::println(String text) {
  Serial.println(text);

  File logFile = SD.open(LOG_FILE, FILE_WRITE);
  if (logFile) {
    logFile.println(text);
    logFile.close();
  } else {
    Serial.println("Unable to write to log");
  }
}
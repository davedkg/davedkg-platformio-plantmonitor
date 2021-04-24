#include <Arduino.h>
#include "RGBLed.h"

RGBLed::RGBLed(int redPin, int greenPin, int bluePin)
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  _redPin = redPin;
  _greenPin = greenPin;
  _bluePin = bluePin;
  off();
}

void RGBLed::off()
{
  digitalWrite(_redPin, LOW);
  digitalWrite(_greenPin, LOW);
  digitalWrite(_bluePin, LOW);
}

void RGBLed::red()
{
  digitalWrite(_redPin, HIGH);
  digitalWrite(_greenPin, LOW);
  digitalWrite(_bluePin, LOW);
}

void RGBLed::green()
{
  digitalWrite(_redPin, LOW);
  digitalWrite(_greenPin, HIGH);
  digitalWrite(_bluePin, LOW);
}

void RGBLed::blue()
{
  digitalWrite(_redPin, LOW);
  digitalWrite(_greenPin, LOW);
  digitalWrite(_bluePin, HIGH);
}
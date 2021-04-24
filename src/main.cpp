#include <Arduino.h>
#include "RGBLed.h"

// RGB LED
RGBLed led(D3, D4, D7);

void setup() {

}

void loop() {
  led.red();
  delay(500);
  led.green();
  delay(500);
  led.blue();
  delay(500);
}
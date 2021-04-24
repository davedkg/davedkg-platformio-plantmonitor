#include <Arduino.h>

// *** RGB LED
#include "RGBLed.h"
RGBLed led(D3, D4, D7);

// *** Display
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setupDisplay() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("SSD1306 allocation failed");
    for(;;); // Don't proceed, loop forever
  }
}

void displaySplash() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("PlantMonitor");
  display.setCursor(0, 8);
  display.println("by DaveDKG");
  display.setCursor(0, 16);
  display.println("v1.01");
  display.display();
}

// *** Lifecycle

void setup() {
  Serial.begin(115200);
  led.off();
  setupDisplay();

  displaySplash();
  delay(2000);
}

void loop() {

}
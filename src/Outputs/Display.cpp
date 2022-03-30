#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Display.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 *_display;

Display::Display()
{
  _display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

  if(!_display->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("SSD1306 allocation failed");
    for(;;); // Don't proceed, loop forever
  }
}

void Display::splash(bool connecting, bool pinging)
{
  _display->clearDisplay();
  _display->setTextSize(1);
  _display->setTextColor(SSD1306_WHITE);
  _display->setCursor(0, 0);
  _display->println("PlantMonitor v1.0");
  _display->setCursor(0, 8);
  _display->println("by DaveDKG");
  _display->setCursor(0, 16);

    if (true == connecting) {
    _display->println("connecting to wifi...");
  } else {
    _display->println("connected to wifi");
  }
  _display->setCursor(0, 24);

  if (true == pinging) {
    _display->println("connecting to api...");
  } else {
    _display->println("connected to api");
  }

  _display->display();
}

void Display::update(int soilMoisture, float temperature, float humidity, bool raining) {
  char buffer[32];

  _display->clearDisplay();
  _display->setTextSize(1);
  _display->setTextColor(SSD1306_WHITE);

  sprintf(buffer, "Soil Moisture: %d%%", soilMoisture);
  _display->setCursor(0, 0);
  _display->println(buffer);

  sprintf(buffer, "Temp: %0.1f C", temperature);
  _display->setCursor(0, 8);
  _display->println(buffer);

  sprintf(buffer, "Humidity: %0.1f%%", humidity);
  _display->setCursor(0, 16);
  _display->println(buffer);

  sprintf(buffer, "Raining: %s", (raining ? "yes" : "no"));
  _display->setCursor(0, 24);
  _display->println(buffer);

  _display->display();
}
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Display.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
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

  _line1 = centerText("Plant Monitor");
  _line2 = "---------------------";

  drawSplash(unknown, unknown);
}

void Display::turnOff() {
  _display->ssd1306_command(SSD1306_DISPLAYOFF);
}

void Display::drawSplash(connectionState wifiConnectionState, connectionState apiConnectionState)
{
  switch (wifiConnectionState) {
    case connecting:
      _line3 = centerText("wifi: ...");
      break;
    case connected:
      _line3 = centerText("wifi: success");
      break;
      case failed:
      _line3 = centerText("wifi: failed!");
      break;
    default:
      _line3 = centerText("wifi: ?");
      break;
  }

  switch (apiConnectionState) {
    case connecting:
      _line4 = centerText("api: ...");
      break;
    case connected:
      _line4 = centerText("api: success");
      break;
      case failed:
      _line4 = centerText("api: failed!");
      break;
    default:
      _line4 = centerText("api: ?");
      break;
  }

  _line5 = "";
  _line6 = "";
  _line7 = "";
  _line8 = centerText("by: davedkg");

  draw();
}

void Display::drawCalibrations(int16_t lightSensor, int16_t rainSensor, int16_t soilSensor1, int16_t soilSensor2) {
  _line3 = "";
  _line4 = "";
  _line5 = justifyText("Light:", String(lightSensor));
  _line6 = justifyText("Raining:", String(rainSensor));
  _line7 = justifyText("Soil 1:", String(soilSensor1));
  _line8 = justifyText("Soil 2:", String(soilSensor2));

  draw();
}

void Display::drawReadings(float atmosphereTemperature, float atmosphereHumidity, float soilMoisture1, float soilMoisture2, float lightIntensity, bool raining) {
  _line3 = justifyText("Temperature:", String(atmosphereTemperature) + "C");
  _line4 = justifyText("Humidity:", String(atmosphereHumidity) + "%");
  _line5 = justifyText("Light:", String(lightIntensity) + "%");
  _line6 = justifyText("Raining:",  String(raining ? "yes" : "no"));
  _line7 = justifyText("Soil 1:", String(soilMoisture1) + "%");
  _line8 = justifyText("Soil 2:", String(soilMoisture2) + "%");

  draw();
}

// *** Private

String Display::justifyText(String leftText, String rightText) {
  String spaces = "";
  int numSpaces = 21 - (leftText.length() + rightText.length());

  for (int i = 0; i < numSpaces; i++) {
    spaces += " ";
  }

  return leftText + spaces + rightText;
}

String Display::centerText(String text) {
  String spaces = "";
  int numSpaces = (21 - text.length()) / 2;

  for (int i = 0; i < numSpaces; i++) {
    spaces += " ";
  }

  return spaces + text;
}

void Display::draw() {
  _display->clearDisplay();
  _display->setTextSize(1);
  _display->setTextColor(SSD1306_WHITE);

  if (!_line1.isEmpty()) {
    _display->setCursor(0, 0);
    _display->println(_line1);
  }

  if (!_line2.isEmpty()) {
    _display->setCursor(0, 8);
    _display->println(_line2);
  }

  if (!_line3.isEmpty()) {
    _display->setCursor(0, 16);
    _display->println(_line3);
  }

  if (!_line4.isEmpty()) {
    _display->setCursor(0, 24);
    _display->println(_line4);
  }

  if (!_line5.isEmpty()) {
    _display->setCursor(0, 32);
    _display->println(_line5);
  }

  if (!_line6.isEmpty()) {
    _display->setCursor(0, 40);
    _display->println(_line6);
  }

  if (!_line7.isEmpty()) {
    _display->setCursor(0, 48);
    _display->println(_line7);
  }

  if (!_line8.isEmpty()) {
    _display->setCursor(0, 56);
    _display->println(_line8);
  }

  _display->ssd1306_command(SSD1306_DISPLAYON);
  _display->display();
}

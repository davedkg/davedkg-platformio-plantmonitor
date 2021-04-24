#include <Arduino.h>
#include "Credentials.h"

// *** RGB LED
#include "Outputs/RGBLed.h"
RGBLed led(D3, D4, D7);

// *** Soil Monitor
#include "Sensors/SoilSensor.h"
#define WET_SOIL_MOISTURE_CAPACITANCE 1265
#define DRY_SOIL_MOISTURE_CAPACITANCE 2970
SoilSensor soilSensor(D6, WET_SOIL_MOISTURE_CAPACITANCE, DRY_SOIL_MOISTURE_CAPACITANCE);

// *** Atmosphere Monitor
#include "Sensors/AtmosphereSensor.h"
AtmosphereSensor* atmosphereSensor = new AtmosphereSensor(D5);

// ** WiFi
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

void setupWifi() {
  led.blue();
  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.hostname(WIFI_DEVICE_NAME);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  int counter = 0;
  while (WL_CONNECTED != WiFi.status()) {
    delay(500);
    Serial.print(".");
    counter++;
    if (60 < counter) {
      led.red();
      Serial.println();
      Serial.println(F("Failed to connect to Wifi"));
      delay(5000);
      ESP.restart();
    }
  }
  led.green();
}

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
  display.println("v1.0");
  display.display();
}

void displayValues(int soilMoisture, float temperature, float humidity) {
  char buffer[32];

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  sprintf(buffer, "Soil Moisture: %d%%", soilMoisture);
  display.setCursor(0, 0);
  display.println(buffer);

  sprintf(buffer, "Temp: %0.1f C", temperature);
  display.setCursor(0, 8);
  display.println(buffer);

  sprintf(buffer, "Humidity: %0.1f%%", humidity);
  display.setCursor(0, 16);
  display.println(buffer);

  display.display();
}

// *** Lifecycle

void setup() {
  Serial.begin(115200);
  setupDisplay();
  displaySplash();

  setupWifi();

  delay(5000);
  led.off();
}

void loop() {
  displayValues(soilSensor.moisture(), atmosphereSensor->temperature(), atmosphereSensor->humidity());
  delay(5000);
}
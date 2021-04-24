#include <Arduino.h>

// *** RGB LED
#include "RGBLed.h"
RGBLed led(D3, D4, D7);

// *** Soil Monitor
#include "SoilMonitor.h"
#define SOIL_MOISTURE_PIN D6
#define WET_SOIL_MOISTURE_CAPACITANCE 1265
#define DRY_SOIL_MOISTURE_CAPACITANCE 2970
SoilMonitor soilMonitor(SOIL_MOISTURE_PIN, WET_SOIL_MOISTURE_CAPACITANCE, DRY_SOIL_MOISTURE_CAPACITANCE);

// *** Atmosphere Monitor
#include <DHT.h>
#include <DHT_U.h>
#define DHT22_PIN D5
#define DHTTYPE DHT22
DHT_Unified atmosphereMonitor(DHT22_PIN, DHTTYPE);

void setupAtmosphereMonitor() {
  atmosphereMonitor.begin();
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

void displaySensorData() {
  sensors_event_t event;
  atmosphereMonitor.temperature().getEvent(&event);
  float temperatureValue = event.temperature;
  atmosphereMonitor.humidity().getEvent(&event);
  float humidityValue = event.relative_humidity;

  displayValues(soilMonitor.moisture(), temperatureValue, humidityValue);
}

// *** Lifecycle

void setup() {
  Serial.begin(115200);
  setupDisplay();
  setupAtmosphereMonitor();

  displaySplash();
  delay(5000);
}

void loop() {
  displaySensorData();
  delay(5000);
}
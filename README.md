# davedkg-platformio-plantmonitor

## TODOS

- how to calibrate soil moisture sensor wet and dry values
- how to calibrate rain sensor
- how to setup in VSCode

## Local Setup

### Credentials

Create src/Credentials.h with the following code.

```cpp
#ifndef CREDENTIALS_H
#define CREDENTIALS_H

char API_DOMAIN[] = "<YOUR_API_DOMAIN>";
char YOUR_API_KEY[] = "<YOUR_API_KEY>";
char WIFI_DEVICE_NAME[] = "<DEVICE_NAME>";
char WIFI_SSID[] = "<YOUR_NETWORK_NAME>";
char WIFI_PASSWORD[] = "<YOUR_NETWORK_PASSWORD>";
char PLANT_1_API_KEY[] = "<YOUR_FIRST_PLANT_API_KEY>";
char PLANT_2_API_KEY[] = "<YOUR_SECOND_PLANT_API_KEY>";

#endif
```

### Calibrations

Create src/Calibrations.h with the following code.

```cpp
#ifndef CALIBRATIONS_H
#define CALIBRATIONS_H

float RAIN_SENSOR_THRESHOLD = 950.0f;
float SOIL_SENSOR_1_MIN_THRESHOLD = 360.0f;
float SOIL_SENSOR_1_MAX_THRESHOLD = 830.0f;
float SOIL_SENSOR_2_MIN_THRESHOLD = 360.0f;
float SOIL_SENSOR_2_MAX_THRESHOLD = 830.0f;

#endif
```

## Hardware

- ESP8266 NodeMCU CP2102 ESP-12E
- DHT22 Digital Temperature and Humidity Sensor
- EK1940 Capacitive Soil Moisture Sensor
- SSD1306 128x32 OLED Screen
- LM393 Rain Drops Sensor
- ADS1015 Analog 4 Channel Analog Gain Amplifier
- RGB Led with 3 x 220 ohm resistors
- Breadboard and wires

## Wiring Diagram

![](docs/PlantMonitor_bb.png)
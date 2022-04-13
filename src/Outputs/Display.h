#ifndef Display_h
#define Display_h

#include <Arduino.h>

enum connectionState {
  unknown,
  connecting,
  connected,
  failed
};

class Display
{
  public:
    Display();
    void drawSplash(connectionState wifiConnectionState, connectionState apiConnectionState);
    void drawCalibrations(int16_t lightSensor, int16_t rainSensor, int16_t soilSensor1, int16_t soilSensor2);
    void drawReadings(float atmosphereTemperature, float atmosphereHumidity, float soilMoisture1, float soilMoisture2, float lightIntensity, bool raining);

  private:
    String _line1;
    String _line2;
    String _line3;
    String _line4;
    String _line5;
    String _line6;
    String _line7;
    String _line8;
    String justifyText(String leftText, String rightText);
    String centerText(String text);
    void draw();
};

#endif
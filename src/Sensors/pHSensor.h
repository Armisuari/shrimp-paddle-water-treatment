#pragma once

#include <DFRobot_ESP_PH_WITH_ADC.h>
#include <Adafruit_ADS1X15.h>
#include <EEPROM.h>

typedef struct 
{
  
  float voltage;
  float value;

}pH_Value;

class pHSensor
{
  public:
    pHSensor(int ADSPin);
    ~pHSensor();

    bool init();
    void calibrate(pH_Value value);
    bool measure(pH_Value& value);

  protected:
    Adafruit_ADS1115 ads;

  private:
    DFRobot_ESP_PH_WITH_ADC ph;
    int _ADSPin;
    static unsigned long timepoint;
    bool _isMeasuring;
    bool _startMillis;
};
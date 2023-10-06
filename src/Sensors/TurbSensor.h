#pragma once

#include <Wire.h>
#include <ADS1X15.h>
#include <EEPROM.h>

typedef struct
{

    float voltage;
    float value;

} Turb_Value;

class TurbSensor
{
public:
    TurbSensor(int ADSPin);
    ~TurbSensor();

    bool init(int lvlVoltage);
    void calibrate(Turb_Value value);
    bool measure(Turb_Value &value);

protected:
    ADS1115 ADS;

private:
    int _ADSPin;
    static unsigned long timepoint;
    bool _isMeasuring;
    bool _startMillis;
    int _lvlVoltage;
};
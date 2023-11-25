#pragma once

#include <Adafruit_ADS1X15.h>
#include <DFRobot_ESP_EC.h>
#include <EEPROM.h>
#include "DS18b20.h"

typedef struct
{
    float voltage;
    float value;
} EC_Value;

class ECSensor
{
public:
    ECSensor(int ADSPin);
    ~ECSensor();

    bool init(Temperature_t Tcompensation);
    void calibrate(EC_Value& _value);
    bool measure(EC_Value& _value, Temperature_t Tcompensation);

protected:
    Adafruit_ADS1115 ads;

private:
    DFRobot_ESP_EC ec;
    int _ADSPin;
    float _temp;
    static unsigned long timepoint;
    bool _isMeasureing;
    bool _startMillis;
};
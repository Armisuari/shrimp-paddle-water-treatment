#pragma once

#include <OneWire.h>

#define TEMP_TAG "Temperature"

struct Temperature_t
{
    float temp;
};

class DS18B20
{
public:
    DS18B20(uint8_t pin);
    ~DS18B20();
    bool begin();
    void measure(Temperature_t &value);

private:
    float getValue();

    OneWire ds;

    bool isDetected;
    uint8_t _pin;
    byte addr[8];
};
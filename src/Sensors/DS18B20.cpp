#include "DS18b20.h"

DS18B20::DS18B20(uint8_t pin) : ds(pin), isDetected(false), _pin(pin) {}

DS18B20::~DS18B20() {}

bool DS18B20::begin()
{
    // Initialize DS18B20 sensor and check for presence
    ds.reset_search();
    if (!ds.search(addr))
    {
        isDetected = false;
        return false;
    }

    if (OneWire::crc8(addr, 7) != addr[7])
    {
        isDetected = false;
        return false;
    }

    if (addr[0] != 0x10 && addr[0] != 0x28)
    {
        isDetected = false;
        return false;
    }

    isDetected = true;
    return true;
}

void DS18B20::measure(Temperature_t &value)
{
    if (!isDetected)
    {
        value.temp = -127.0; // Return an invalid temperature value
        return;
    }

    float temperature = getValue();
    value.temp = temperature;
}

float DS18B20::getValue()
{
    ds.reset();
    ds.select(addr);
    ds.write(0x44); // Start temperature conversion
    delay(750);     // Wait for conversion to complete

    ds.reset();
    ds.select(addr);
    ds.write(0xBE); // Read scratchpad

    byte data[9];
    for (uint8_t i = 0; i < 9; i++)
    {
        data[i] = ds.read();
    }

    int16_t rawTemperature = ((int16_t)data[1] << 8) | data[0];
    float temperature = (float)rawTemperature / 16.0;

    return temperature;
}

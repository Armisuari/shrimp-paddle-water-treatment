#include "TurbSensor.h"

#define TURB_SENSOR_TAG "Turbidity"

unsigned long TurbSensor::timepoint = 1000;

TurbSensor::TurbSensor(int ADSPin) : _ADSPin(ADSPin)
{
}

TurbSensor::~TurbSensor()
{
}

bool TurbSensor::init(int lvlVoltage)
{
    EEPROM.begin(34);

    if (!ADS.begin())
    {
        _isMeasuring = false;
        ESP_LOGE(TURB_SENSOR_TAG, "Failed to detect ADS1115");
        return false;
    }

    _lvlVoltage = lvlVoltage;
    _isMeasuring = true;
    return true;
}

void TurbSensor::calibrate(Turb_Value value)
{

}

bool TurbSensor::measure(Turb_Value& value)
{
    ADS.setGain(0);

    if (!_isMeasuring)
    {
        ESP_LOGW(TURB_SENSOR_TAG, "Failed to read turbidity value");
        return false;
    }

    _startMillis = millis();
    if (millis() - _startMillis < timepoint)
    {
        ESP_LOGI(TURB_SENSOR_TAG, "Waiting for the sensor to be ready...");
        return false;
    }

    value.voltage = ADS.readADC(_ADSPin);
    value.value = value.voltage * (_lvlVoltage / 65536.0);

    return true;
}
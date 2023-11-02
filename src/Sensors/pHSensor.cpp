#include "pHSensor.h"

#define PH_SENSOR_TAG "pHSensor"

unsigned long pHSensor::timepoint = 1000;

pHSensor::pHSensor(int ADSPin) : _ADSPin(ADSPin)
{
}

pHSensor::~pHSensor()
{
}

bool pHSensor::init()
{
    EEPROM.begin(33);

    if(!ads.begin())
    {
        _isMeasuring = false;
        ESP_LOGE(PH_SENSOR_TAG, "Failed to detect ADS1115");
        return false;
    }

    _isMeasuring = true;
    ph.begin();
    ads.setGain(GAIN_ONE);

    return true;
}

void pHSensor::calibrate(pH_Value _value)
{
    ESP_LOGI(PH_SENSOR_TAG, "Starting pH sensor calibration...");
    ph.calibration(_value.voltage, 25);
}

bool pHSensor::measure(pH_Value &_value)
{
    if (!_isMeasuring)
    {
        ESP_LOGW(PH_SENSOR_TAG, "Failed to read pH value");
        return false;
    }

    _startMillis = millis();
    if (millis() - _startMillis < timepoint)
    {
        ESP_LOGI(PH_SENSOR_TAG, "Waiting for the sensor to be ready...");
        return false;
    }

    _value.voltage = ads.readADC_SingleEnded(_ADSPin) / 10;
    _value.value = ph.readPH(_value.voltage,25); // ec.readEC(_value.voltage, _temp);

    return true;
}
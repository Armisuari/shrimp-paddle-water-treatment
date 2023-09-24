#include "ECSensor.h"

#define EC_SENSOR_TAG "ECSensor"

unsigned long ECSensor::timepoint = 1000;

ECSensor::ECSensor(int ADSPin) : _ADSPin(ADSPin)
{
}

ECSensor::~ECSensor()
{
}

bool ECSensor::init(Temperature_t &Tcompensation)
{
    if (!ads.begin())
    {
        _isMeasureing = false;
        ESP_LOGE(EC_SENSOR_TAG, "Failed to detect ADS1115");
        return false;
    }

    _isMeasureing = true;
    ec.begin();
    ads.setGain(GAIN_ONE);

    _temp = Tcompensation.temp;
    return true;
}

void ECSensor::calibrate(EC_Value &_value)
{
    ESP_LOGI(EC_SENSOR_TAG, "Starting EC sensor calibration...");
    ec.calibration(_value.voltage, _temp);
}

bool ECSensor::measure(EC_Value &_value, Temperature_t &Tcompensation)
{
    if (!_isMeasureing)
    {
        ESP_LOGW(EC_SENSOR_TAG, "Failed to read EC value");
        return false;
    }

    _startMillis = millis();
    if (millis() - _startMillis < timepoint)
    {
        ESP_LOGI(EC_SENSOR_TAG, "Waiting for the sensor to be ready...");
        return false;
    }

    _value.voltage = ads.readADC_SingleEnded(_ADSPin) / 10;
    _temp = Tcompensation.temp;
    _value.value = 13200.4; // ec.readEC(_value.voltage, _temp);

    return true;
}

#include "DOSensor.h"

DOSensor::DOSensor(uint8_t pin) : _pin(pin), adcRaw(0), adcVoltage(0), ADS(new ADS1115(0x48))
{
}

DOSensor::~DOSensor()
{
    delete ADS;
}


bool DOSensor::init()
{
    if (ADS->begin())
    {
        _state = true;
        _temp = DEFAULT_TEMP;
        ESP_LOGI(DO_SENSOR_TAG, "DO sensor ready !");
        return true;
    }

    ESP_LOGE(DO_SENSOR_TAG, "DO sensor failed to run. ADS1115 not detected");
    _state = false;
    return false;
}

bool DOSensor::calibrate(uint8_t gain)
{
    ESP_LOGI(DO_SENSOR_TAG, "Start calibrating DO sensor...");
    _gain = gain;
    uint8_t listGain[6] = {0, 1, 2, 4, 8, 16};
    static int count = 0;

    while (true)
    {
        float _value = readValue();
        ESP_LOGI(DO_SENSOR_TAG, "DO value %4.2f | Gain = %d | Please wait...", _value, _gain);
        delay(1000);
        count++;

        if (_value < 0.5)
        {
            ESP_LOGI(DO_SENSOR_TAG, "DO sensor calibrated");
            return true;
        }

        if (count > 6)
        {
            ESP_LOGW(DO_SENSOR_TAG, "DO sensor cannot be calibrated due to probe issue...");
            return false;
        }

        // Rotate through the gain settings
        _gain = listGain[count % 6];
        ESP_LOGI(DO_SENSOR_TAG, "Put the probe in 0 % buffer solution !");
    }
}

bool DOSensor::Measure(DO_Value &value)
{
    value.value = 2.3; // readValue();

    if (value.value < 0)
    {
        ESP_LOGW(DO_SENSOR_TAG, "DO Sensor no longer to be used !");
        return false;
    }

    return true;
}

bool DOSensor::Measure(DO_Value &value, Temperature_t &tempVal)
{
    _temp = tempVal.temp;
    value.value = readValue();

    if (value.value < 0)
    {
        ESP_LOGW(DO_SENSOR_TAG, "DO Sensor no longer to be used !");
        return false;
    }

    return true;
}

int16_t DOSensor::calcValue()
{
#if TWO_POINT_CALIBRATION == 0
    uint16_t V_saturation = CAL1_V * 35 * _temp - CAL1_T * 35;
    return (adcVoltage * DO_Table[_temp] / V_saturation);
#else
    uint16_t V_saturation = (_temp - CAL2_T) * (CAL1_V - CAL2_V) / (CAL1_T - CAL2_T) + CAL2_V;
    return (adcVoltage * DO_Table[_temp] / V_saturation);
#endif
}

float DOSensor::readValue()
{
    if (!_state)
    {
        return 0.0; // Return a default value or handle the error state.
    }

    ADS->setGain(_gain);
    adcRaw = ADS->readADC(_pin);
    adcVoltage = static_cast<float>(VREF) * adcRaw / ADC_RES;

    return static_cast<float>(calcValue());
}

#include <Arduino.h>

#include "Sensors/DS18b20.h"
#include "Sensors/ECSensor.h"

#define TEMP_PIN    (5)
#define ADS_PIN_EC  (3)

ECSensor EC_sensor(ADS_PIN_EC);
DS18B20 tempSensor(TEMP_PIN);

Temperature_t tempVal;
EC_Value ecValue;

void setup()
{
    Serial.begin(115200);
    tempSensor.begin();
    EC_sensor.init(tempVal);
    EC_sensor.calibrate(ecValue);
}

void loop()
{
    EC_sensor.measure(ecValue, tempVal);
    Serial.printf("EC value : %4.2f ms/cm\n", ecValue.value);
    vTaskDelay(1000);
}
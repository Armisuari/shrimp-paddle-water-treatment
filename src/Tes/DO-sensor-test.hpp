#pragma once
#include <Arduino.h>

#include "Sensors/DOSensor.h"
#include "Sensors/DS18B20.h"

#define TEMP_PIN 5
#define DO_PIN_ADS 2

DS18B20 tempSensor(TEMP_PIN);
DOSensor DO_sensor(DO_PIN_ADS); 

Temperature_t tempVal;
DO_Value DOvalue;

void setup()
{
    Serial.begin(115200);
    delay(1000);

    tempSensor.begin();
    tempSensor.measure(tempVal);

    DO_sensor.init();
    // DO_sensor.calibrate(0);
    // DO_sensor.Measure(DOvalue);
    DO_sensor.Measure(DOvalue, tempVal);

    // Serial.printf("Temperature value : %4.2f %\n", tempVal.temp);

    // Serial.printf("DO value : %4.2f %\n", DOvalue.value);
    Serial.printf("DO value : %4.2f % | Temp : %4.2f ℃\n", DOvalue.value, tempVal.temp);
}

void loop()
{
    vTaskDelete(NULL);
}
#include <Arduino.h>

#include "Sensors/TurbSensor.h"

#define ADS_PIN_TURB  (1)
const int level_voltage = 5; //v

TurbSensor turbSensor(ADS_PIN_TURB);
Turb_Value turbValue;

void setup()
{
    Serial.begin(115200);
    turbSensor.init(static_cast<float>(level_voltage));
    // turbSensor.calibrate(turbValue);
}

void loop()
{
    turbSensor.measure(turbValue);
    Serial.printf("turbidity value : %4.2f\n", turbValue.value);
    vTaskDelay(1000);
}
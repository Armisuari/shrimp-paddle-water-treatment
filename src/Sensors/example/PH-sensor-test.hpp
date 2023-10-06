#include <Arduino.h>

#include "Sensors/pHSensor.h"

#define ADS_PIN_PH  (1)

pHSensor pH_sensor(ADS_PIN_PH);
pH_Value phValue;

void setup()
{
    Serial.begin(115200);
    pH_sensor.init();
    pH_sensor.calibrate(phValue);
}

void loop()
{
    pH_sensor.measure(phValue);
    Serial.printf("pH value : %4.2f\n", phValue.value);
    vTaskDelay(1000);
}
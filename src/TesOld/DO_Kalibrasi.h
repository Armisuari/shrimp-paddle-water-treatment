#include <Arduino.h>

#define VREF    3300//VREF(mv)
#define ADC_RES 65536//ADC Resolution
#include"ADS1X15.h"

ADS1115 ADS(0x48);
uint32_t raw;

void setup()
{
    Serial.begin(115200);
    ADS.begin();
}

void loop()
{
    ADS.setGain(0); // setGain set to 1 to more precission
    raw=ADS.readADC(2);
    Serial.println("raw:\t"+String(raw)+"\tVoltage(mv)"+String(raw*VREF/ADC_RES));
    delay(1000);
}
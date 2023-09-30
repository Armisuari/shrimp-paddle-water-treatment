#pragma once

#include <Wire.h>
#include <ADS1X15.h>
#include <EEPROM.h>

typedef struct
{

    float voltage;
    float value;

} Turb_Value;

class TurbSensor
{
public:
    TurbSensor(int ADSPin);
    ~TurbSensor();

    bool init(int lvlVoltage);
    void calibrate(Turb_Value value);
    bool measure(Turb_Value &value);

protected:
    ADS1115 *ADS;

private:
    int _ADSPin;
    static unsigned long timepoint;
    bool _isMeasuring;
    bool _startMillis;
    int _lvlVoltage;
};

// ADS1115 ADS(0x48);

// void setup (){
//     Serial.begin(115200);
//     ADS.begin();
// }

// void loop (){
//     ADS.setGain(0); // setGain set to 1 to more precission
//     int nilai_turbidity = ADS.readADC(0);
//     float voltage = nilai_turbidity * (3.3 / 65536.0);
//     // float voltage = nilai_turbidity * (5.0 / 1024.0);
//     Serial.printf("Nilai tegangan = %f\n", nilai_turbidity);
//     delay(10);
// }
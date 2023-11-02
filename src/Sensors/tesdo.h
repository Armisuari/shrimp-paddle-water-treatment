#pragma once
#include <Arduino.h>
#include "ADS1X15.h"

#define VREF 3300        // VREF (mV)
// #define ADC_RES 26470   // ADC Resolution
#define ADC_RES 5000
#define TWO_POINT_CALIBRATION 0

#define READ_TEMP (20) //Current water temperature ℃, Or temperature sensor function

//Single point calibration needs to be filled CAL1_V and CAL1_T
#define CAL1_V (1250) //mv
#define CAL1_T (33)   //℃
//Two-point calibration needs to be filled CAL2_V and CAL2_T
//CAL1 High temperature point, CAL2 Low temperature point
#define CAL2_V (1300) //mv
#define CAL2_T (15)   //℃

ADS1115 ADS(0x48);

class DO_Sensor {
private:
uint8_t temperature;
  uint16_t adcRaw;
  uint16_t adcVoltage;

  const uint16_t DO_Table[41] = {
    14460, 14220, 13820, 13440, 13090, 12740, 12420, 12110, 11810, 11530,
    11260, 11010, 10770, 10530, 10300, 10080, 9860, 9660, 9460, 9270,
    9080, 8900, 8730, 8570, 8410, 8250, 8110, 7960, 7820, 7690,
    7560, 7430, 7300, 7180, 7070, 6950, 6840, 6730, 6630, 6530, 6410};

public:
  DO_Sensor() : adcRaw(0), adcVoltage(0) {}
  

  void setup() {
    Serial.begin(115200);
    ADS.begin();
  }

  float readDO() {
    temperature = READ_TEMP;
    ADS.setGain(0);
    adcRaw = ADS.readADC(2);
    adcVoltage = uint32_t(VREF) * adcRaw / ADC_RES;

    // Serial.print("ADC RAW:\t" + String(adcRaw) + "\t");
    // Serial.print("ADC Voltage:\t" + String(adcVoltage) + "\t");
    // Serial.println("DO:\t" + String(calculateDO()) + "\t");
    float data = calculateDO();
    return data;

    delay(500);
  }
  int data(){
    return calculateDO();
  }

private:
  int16_t calculateDO() {
    #if TWO_POINT_CALIBRATION == 0
      uint16_t V_saturation = CAL1_V + 35 * temperature - CAL1_T * 35;
      return (adcVoltage * DO_Table[temperature] / V_saturation);
    #else
      uint16_t V_saturation = (int16_t)(temperature - CAL2_T) * (CAL1_V - CAL2_V) / (CAL1_T - CAL2_T) + CAL2_V;
      return (adcVoltage * DO_Table[temperature] / V_saturation);
    #endif
  }
};

DO_Sensor sensor;

// void setup() {
//   sensor.setup();
// }

// void loop() {
//   sensor.readDO();
// }

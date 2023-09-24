#pragma once
#include <Arduino.h>
#include "ADS1X15.h"

#include "DS18b20.h"

#define VREF 3300     // VREF (mV)
#define ADC_RES 26470 // ADC Resolution
#define TWO_POINT_CALIBRATION 0

// Single point calibration needs to be filled CAL1_V and CAL1_T
#define CAL1_V (1250) // mv
#define CAL1_T (33)   // ℃

// Two-point calibration needs to be filled CAL2_V and CAL2_T
// CAL1 High temperature point, CAL2 Low temperature point
#define CAL2_V (1300) // mv
#define CAL2_T (15)   // ℃

#define DO_SENSOR_TAG "DO_Sensor"

typedef struct
{
  float value;
} DO_Value;

class DOSensor
{
private:
  const uint16_t DO_Table[41] = {
      14460, 14220, 13820, 13440, 13090, 12740, 12420, 12110, 11810, 11530,
      11260, 11010, 10770, 10530, 10300, 10080, 9860, 9660, 9460, 9270,
      9080, 8900, 8730, 8570, 8410, 8250, 8110, 7960, 7820, 7690,
      7560, 7430, 7300, 7180, 7070, 6950, 6840, 6730, 6630, 6530, 6410};

  uint8_t _pin;
  uint8_t _temp;
  uint16_t adcRaw;
  uint16_t adcVoltage;
  uint8_t _gain;
  bool _state;

  TaskHandle_t taskHandle;
  ADS1115 *ADS;

  int16_t calcValue();
  float readValue();

public:
  DOSensor(uint8_t pin);
  ~DOSensor();

  bool init();
  bool calibrate(uint8_t gain);
  bool Measure(DO_Value &value);
  bool Measure(DO_Value &value, Temperature_t &tempVal);
};

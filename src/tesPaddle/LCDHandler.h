#pragma once
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

class LCDHandler
{
  public:
  bool init();
  void cetak(int rows, int columns, String teks);
};

// void setup()
// {
  // lcd.init();                      // initialize the lcd 
  // lcd.backlight();
// }

// void loop()
// {
//     lcd.clear();
//     lcd.print("tes");
// }
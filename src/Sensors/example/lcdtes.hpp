//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C mylcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  mylcd.init();                      // initialize the mylcd 
  // Print a message to the mylcd.
  mylcd.backlight();
}


void loop()
{
    mylcd.clear();
    mylcd.setCursor(3,0);
    mylcd.print("Hello, world!");
    mylcd.setCursor(2,1);
    mylcd.print("Ywrobot Arduino!");
    mylcd.setCursor(0,2);
    mylcd.print("Arduino LCM IIC 2004");
    mylcd.setCursor(2,3);
    mylcd.print("Power By Ec-yuan!");
    delay(300);
}

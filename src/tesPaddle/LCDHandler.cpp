#include "LCDHandler.h"
LiquidCrystal_I2C lcd(0x27,20,4);


bool LCDHandler::init()
{
    lcd.init();
    lcd.backlight();

    return true;
}
void LCDHandler::cetak(int rows, int columns, String teks) {
    // lcd.clear();
    lcd.setCursor(rows,columns);
    lcd.print(teks);
}
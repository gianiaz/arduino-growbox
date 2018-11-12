#include "Arduino.h"
#include "LcdWrapper.h"
#include "Time.h"
#include "PCF8574_HD44780_I2C.h"


LcdWrapper::LcdWrapper(): _lcd(0x3F,16,2)
{
}

void LcdWrapper::setUp(bool debug) {
  _debug = debug;
  _lcd.init();
  _lcd.backlight();
}

void LcdWrapper::printLines(String line1, String line2) {
  if(_debug) {
    Serial.println("Printing...");
    Serial.println(line1);
    Serial.println("Printing...");
    Serial.println(line2);
  }
  _lcd.clear();
  _lcd.setCursor(0,0);
  _lcd.print(line1);
  _lcd.setCursor(0,1);
  _lcd.print(line2);
}

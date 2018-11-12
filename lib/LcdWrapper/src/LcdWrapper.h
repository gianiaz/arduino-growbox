#include "Arduino.h"
#include "PCF8574_HD44780_I2C.h"
#ifndef LcdWrapper_h
#define LcdWrapper_h

class LcdWrapper
{
  public:
    LcdWrapper();
    void updateStatus();
    void setUp(bool debug);
    void printLines(String line1, String line2);
  private:
    PCF8574_HD44780_I2C _lcd;
    int _debug;
};
#endif

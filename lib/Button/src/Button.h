#include "Arduino.h"
#ifndef Button_h
#define Button_h
class Button
{
  public:
    Button(int pin, uint8_t pressMillis);
    void setUp(bool debug);
    bool isPressed();
  private:
    int _pin;
    uint8_t _pressMillis;
    bool _debug;
    unsigned int _lastPress;
};
#endif

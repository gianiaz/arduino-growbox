#include "Arduino.h"
#ifndef Button_h
#define Button_h
class Button
{
  public:
    Button(int pin, unsigned long pressMillis);
    void setUp(bool debug);
    bool isPressed();
  private:
    int _pin;
    unsigned long _pressMillis;
    bool _debug;
    unsigned long _lastPress;
};
#endif

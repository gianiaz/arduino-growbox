#include "Arduino.h"
#ifndef LedLib_h
#define LedLib_h
class LedLib
{
  public:
    LedLib(int pin);
    void blink(unsigned long duration, unsigned long impulse);
    void powerOff();
    void powerOn();
    void updateStatus();
    void setDebug(bool debug);
  private:
    int _pin;
    unsigned int _expire;
    bool _debug;
    String _status;
    bool _isHigh;
    unsigned long _blinkingImpulseTimeout;
    unsigned long _impulse;
    void toggle();
    void doPowerOff();
    void doPowerOn();
};
#endif

#include "Arduino.h"
#ifndef LedLib_h
#define LedLib_h
class LedLib
{
  public:
    LedLib(int pin);
    void blink(int duration, int impulse);
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
    unsigned int _blinkingImpulseTimeout;
    int _impulse;
    void toggle();
    void doPowerOff();
    void doPowerOn();
};
#endif

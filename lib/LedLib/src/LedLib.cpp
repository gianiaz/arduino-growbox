#include "Arduino.h"
#include "LedLib.h"
#include "Time.h"



LedLib::LedLib(int pin)
{
  _pin = pin;
  _debug = false;
  _expire = 0;
  _status = "OFF";
  _isHigh = false;
  _blinkingImpulseTimeout = 0;
  _impulse = 200;
  _debug = false;
}

void LedLib::setUp(bool active, bool debug) {
  _active = active;
  _debug = debug;
  if(_debug) {
    Serial.println("LedLib initialized with pin "+_pin);
  }
  if(_active) {
    pinMode(_pin, OUTPUT);
  }

}

void LedLib::blink(unsigned long duration, unsigned long impulse)
{
  _expire = now()+ duration;
  _status = "BLINKING";
  _impulse = impulse;
  _blinkingImpulseTimeout = millis() + _impulse;
  if(_debug) {
    Serial.print("Blinking for "+String(duration)+" seconds (PIN: "+String(_pin)+")");
  }
}

void LedLib::updateStatus() {
  if(_debug) {
    Serial.print("Led status power: " + _status+ " (PIN: "+String(_pin)+")");
  }

  if(_status == "BLINKING") {
    if(_debug) {
      Serial.println("Millis "+String(millis())+" _blinkingImpulseTimeout: "+String(_blinkingImpulseTimeout));
    }
    if(millis() > _blinkingImpulseTimeout) {
      toggle();
      _blinkingImpulseTimeout = millis() + _impulse;
    }
    if(now() > _expire) {
      doPowerOff();
      _expire = 0;
      _status = "OFF";
    }
  }

}

void LedLib::powerOn()
{
  _status = "ON";
  doPowerOn();
}

void LedLib::powerOff()
{
  _status = "OFF";
  doPowerOff();
}

void LedLib::doPowerOff()
{
  if(_debug) {
    Serial.print("DO Power OFF (PIN: "+String(_pin)+")");
  }
  if(_active) {
    digitalWrite(_pin, LOW);
  }
  _isHigh = false;
}

void LedLib::doPowerOn()
{
  if(_debug) {
    Serial.println("DO Power ON ("+String(_pin)+")");
  }
  if(_active) {
    digitalWrite(_pin, HIGH);
  }
  _isHigh = true;
}

void LedLib::toggle()
{
  if(_isHigh) {
    doPowerOff();
  } else {
    doPowerOn();
  }
}

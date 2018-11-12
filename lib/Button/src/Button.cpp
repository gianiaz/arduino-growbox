#include "Arduino.h"
#include "Button.h"
#include "Time.h"

Button::Button(int pin, uint8_t pressMillis) {
  _pin = pin;
  _pressMillis = pressMillis;
  _lastPress = 0;
}

void Button::setUp(bool debug) {
  _debug = debug;
  if(_debug) {
    Serial.println("Listening for click on pin "+String(_pin)+" (press sensitivity "+String(_pressMillis)+")");
  }
  pinMode(_pin, INPUT);
}

bool Button::isPressed() {
  if(digitalRead(_pin) == LOW) {
    if(_debug) {
      Serial.println("Not pressing button on pin("+String(_pin)+")");
    }
    return false;
  }

  if((millis() - _pressMillis) < _lastPress) {
    if(_debug) {
      Serial.println("Ignoring press on pin("+String(_pin)+")");
    }
    return false;
  }

  if(_debug) {
    Serial.println("Clicked ("+String(_pin)+")");
  }

  _lastPress = millis();

  return true;
}

#include "Arduino.h"
#include "SerialSender.h"
#include "Time.h"



SerialSender::SerialSender(int baudRate, long double updateTimeout)
{
  _baudRate = baudRate;
  _updateTimeout = updateTimeout;
  _lastOperation = 0;
}

void SerialSender::setUp(bool debug) {
  _debug = debug;
  Serial.begin(_baudRate);
}

bool SerialSender::updateStatus(String data) {
  if(_lastOperation + _updateTimeout < millis()) {
    _lastOperation = millis();
    if(!_debug) {
      Serial.println("[growbox]"+data+"[/growbox]");
    }
    return true;
  }
  return false;
}

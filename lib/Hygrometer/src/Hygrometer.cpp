#include "Arduino.h"
#include "Hygrometer.h"
#include "Time.h"


Hygrometer::Hygrometer(uint8_t pin, int secondsDelayBetwenLectures)
{
  _pin = pin;
  _milliseconds_delay_betwen_lectures = secondsDelayBetwenLectures * 1000;
  _last_lecture_time = 0;
  _last_lecture = 0;
}

void Hygrometer::setUp(bool active, bool debug) {
  _active = active;
  _debug = debug;
  if(_active) {
    doRead();
    if(_debug) {
      Serial.println("Debug attivo");
    }
  }
}

String Hygrometer::getHumidity() {
  return String(_last_lecture);
}

void Hygrometer::updateStatus() {

  if((_last_lecture_time + _milliseconds_delay_betwen_lectures) < millis()) {
    _last_lecture_time = millis();
    if(_debug) {
      Serial.println("Reading...");
    }
    doRead();
    if(_debug) {
      Serial.print("Soil humidity: ");
    	Serial.print(_last_lecture);
    	Serial.println("%");
    }
  }

}

void Hygrometer::doRead() {
  if(_active) {
    _last_lecture = analogRead(_pin);		//Read analog value
    if(_debug) {
      Serial.print("Analog lecture: ");
      Serial.println(_last_lecture);
    }
    _last_lecture = constrain(_last_lecture,400,1023);	//Keep the ranges!
    _last_lecture = map(_last_lecture,400,1023,100,0);	//Map value : 400 will be 100 and 1023 will be 0
  }
}

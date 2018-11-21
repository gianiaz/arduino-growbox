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

void Hygrometer::setUp(bool debug) {
  _debug = debug;
}

String Hygrometer::getHumidity() {
  return String(_last_lecture);
}

void Hygrometer::updateStatus() {

  if(millis() > _milliseconds_delay_betwen_lectures && (millis() - _milliseconds_delay_betwen_lectures) > _last_lecture_time) {
    _last_lecture_time = millis();
    if(_debug) {
      Serial.println("Reading...");
    }
    _last_lecture = analogRead(_pin);		//Read analog value
    _last_lecture = constrain(_last_lecture,400,1023);	//Keep the ranges!
  	_last_lecture = map(_last_lecture,400,1023,100,0);	//Map value : 400 will be 100 and 1023 will be 0
    if(_debug) {
      Serial.print("Soil humidity: ");
    	Serial.print(_last_lecture);
    	Serial.println("%");
    }
  }
}

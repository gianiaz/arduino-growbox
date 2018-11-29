#include "Arduino.h"
#include "DayNight.h"
#include "Time.h"
#include "Servo.h"

const int DAY_POSITION = 3;
const int NIGHT_POSITION = 168;

DayNight::DayNight(int pinServo, unsigned char pinPhotoResistor, int threshold, unsigned long bounce)
{
  _pinServo = pinServo;
  _pinPhotoResistor = pinPhotoResistor;
  _threshold = threshold;
  _status = "NIGHT";
  _millis = 0;
  _bounce = bounce;
}

void DayNight::setUp(bool active, bool debug) {
  _lastLecture = 0;
  _active = active;
  _debug = debug;
  if(_debug) {
    //Serial.println("Day night disk, reading photo-resistor from pin "+ String(_pinPhotoResistor)+ ", driving servo from pin "+String(_pinServo));
  }
  if(_active) {
    pinMode(_pinPhotoResistor, INPUT);
    _servo.attach(_pinServo);
    _servo.write(NIGHT_POSITION);
  }
}

void DayNight::setPosition(int position) {
  _servo.write(position);
}

String DayNight::isDay() {
  if(_status == "DAY") {
    return "1";
  }
  return "0";
}

void DayNight::readPhotoResistor() {
  _lastLecture = millis();
  if(_debug) {
    Serial.println("Reading ...");
  }
  _pinPhotoResistorLecture = analogRead(_pinPhotoResistor);
  if(_debug) {
    Serial.print("Light is ");
  }

  if(_pinPhotoResistorLecture > _threshold) {
    if(_debug) {
      Serial.println("ON");
    }
    day();
  } else {
    if(_debug) {
      Serial.println("OFF");
    }
    night();
  }

}

void DayNight::night() {
  if(_status == "DAY") {
    if(_debug) {
      Serial.println("Setting disk to NIGHT position...");
    }
    _status = "NIGHT";
    if(_active) {
      _servo.write(NIGHT_POSITION);
    }
  } else {
    if(_debug) {
      Serial.println("Disk is already in NIGHT position");
    }
  }
}

void DayNight::day() {
  if(_status == "NIGHT") {
    if(_debug) {
      Serial.println("Setting disk to DAY position...");
    }
    _status = "DAY";
    if(_active) {
      _servo.write(DAY_POSITION);
    }
  } else {
    if(_debug) {
      Serial.println("Disk is already in DAY position");
    }
  }
}

void DayNight::updateStatus() {
  if((_lastLecture + _bounce) < millis()) {
    readPhotoResistor();
    if(_debug) {
        Serial.println("Photoresistor value :"+String(_pinPhotoResistorLecture));
    }
  }
}

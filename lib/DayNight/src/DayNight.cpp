#include "Arduino.h"
#include "DayNight.h"
#include "Time.h"
#include "Servo.h"



DayNight::DayNight(int pinServo, unsigned char pinPhotoResistor, int threshold)
{
  _pinServo = pinServo;
  _pinPhotoResistor = pinPhotoResistor;
  _threshold = threshold;
  _status = "DAY";
  _millis = 0;
  pinMode(_pinPhotoResistor, INPUT);
}

void DayNight::setUp() {
  _servo.attach(_pinServo);
  _servo.write(0);
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
  if(_debug) {
    Serial.println("Setting disk to NIGHT position...");
  }
  if(_status == "DAY") {
    _servo.write(168);
    _status = "NIGHT";
  }
}

void DayNight::day() {
  if(_debug) {
    Serial.println("Setting disk to DAY position...");
  }
  if(_status == "NIGHT") {
    _servo.write(0);
    _status = "DAY";
  }
}

void DayNight::updateStatus() {
  readPhotoResistor();
  if(_debug) {
      Serial.println("Photoresistor value :"+String(_pinPhotoResistorLecture));
  }
}

void DayNight::setDebug(bool debug) {
  _debug = debug;
  if(_debug) {
    Serial.println("Day night disk, reading photo-resistor from pin "+ String(_pinPhotoResistor)+ ", driving servo from pin "+String(_pinServo));
  }
}

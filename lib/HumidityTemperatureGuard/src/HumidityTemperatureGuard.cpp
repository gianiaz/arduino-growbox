#include "Arduino.h"
#include "HumidityTemperatureGuard.h"
#include "Time.h"
#include <DHT.h>
#include <DHT_U.h>
#include <math.h>

HumidityTemperatureGuard::HumidityTemperatureGuard(int pinDHT, int pinFan, int pinHumidifier, int fanThreshold, int humidifierThreshold): _dht(pinDHT, DHT22, 6)
{
  _pinFan = pinFan;
  _pinDHT = pinDHT;
  _pinHumidifier = pinHumidifier;
  _debug = false;
  _tolerance = 5;
  _fanThreshold = fanThreshold;
  _humidifierThreshold = humidifierThreshold;
  _thick = 5000;
  _startTime = millis();
  _fanStatus = 0;
  _humidifierStatus = 0;
}

String HumidityTemperatureGuard::getTemperature() {
  if(isnan(_temperature)) {
    return "-";
  }
  return String(_temperature);
}

int HumidityTemperatureGuard::getFanThreshold() {
  return _fanThreshold;
}

int HumidityTemperatureGuard::getHumidifierThreshold() {
  return _humidifierThreshold;
}

String HumidityTemperatureGuard::getHumidity() {
  if(isnan(_humidity)) {
    return "-";
  }
  return String(_humidity);
}

void HumidityTemperatureGuard::setUp(bool debug) {
  _debug = debug;
  pinMode(_pinFan, OUTPUT);
  pinMode(_pinHumidifier, OUTPUT);
  if(_debug) {
    Serial.println("HumidityTemperatureGuard: DHT pin ("+String(_pinDHT)+"), Fan pin ("+String(_pinFan)+"), Humidifier PIN ("+String(_pinHumidifier)+")");
  }
}

String HumidityTemperatureGuard::getFanStatus() {
  return String(_fanStatus);
}
String HumidityTemperatureGuard::getHumidifierStatus() {
  return String(_humidifierStatus);
}

void HumidityTemperatureGuard::activateFans(bool activate) {
  if(_debug) {
    Serial.println("Temperature: "+String(_temperature)+", Humidity: "+_humidity);
    Serial.print("Fan status: ");
  }
  if(activate) {
    digitalWrite(_pinFan, HIGH);
    _fanStatus = 1;
    if(_debug) {
      Serial.println(F("ACTIVE"));
    }
  } else {
    digitalWrite(_pinFan, LOW);
    _fanStatus = 0;
    if(_debug) {
      Serial.println(F("NOT ACTIVE"));
    }
  }
}

void HumidityTemperatureGuard::activateHumidifier(bool activate) {
  if(_debug) {
    Serial.print(F("Humidifier status: "));
  }
  if(activate) {
    digitalWrite(_pinHumidifier, HIGH);
    _humidifierStatus = 1;
    if(_debug) {
      Serial.println(F("ACTIVE"));
    }
  } else {
    digitalWrite(_pinHumidifier, LOW);
    _humidifierStatus = 0;
    if(_debug) {
      Serial.println(F("NOT ACTIVE"));
    }
  }
}

void HumidityTemperatureGuard::setFanThreshold(int threshold) {
  _fanThreshold = threshold;
}

void HumidityTemperatureGuard::setHumidifierThreshold(int threshold) {
  _humidifierThreshold = threshold;
}

void HumidityTemperatureGuard::readTemperatureAndHumidity() {
  sensors_event_t event;
  _dht.temperature().getEvent(&event);

  _temperature = event.temperature;

  // Get temperature event and print its value.
  _dht.humidity().getEvent(&event);

  _humidity = event.relative_humidity;

  if(_debug) {
    Serial.println("Temperature: "+String(_temperature)+", Humidity: "+_humidity);
    Serial.println("Fan Threshold: "+String(_fanThreshold));
    Serial.println("Humidifier Threshold: "+String(_humidifierThreshold));
  }
}

void HumidityTemperatureGuard::updateStatus() {

  if(millis() > _thick && (millis() - _thick) > _startTime) {
    _startTime = millis();
    readTemperatureAndHumidity();
    if(_humidity > (_fanThreshold)) {
      activateFans(true);
    } else {
      if (_humidity < (_fanThreshold)) {
        activateFans(false);
      }
    }
    if(_humidity < (_humidifierThreshold)) {
      activateHumidifier(true);
    } else {
      if (_humidity > (_humidifierThreshold)) {
        activateHumidifier(false);
      }
    }
  } else {
    // Serial.println();
    // Serial.println();
    // Serial.println();
    // Serial.println();
    // int prova =  int(_thick);
    // int prova2 = int(_startTime);
    // Serial.println(String(millis())+", "+prova + ", "+prova2);
  }
}

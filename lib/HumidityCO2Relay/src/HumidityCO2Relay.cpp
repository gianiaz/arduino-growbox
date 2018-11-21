#include "Arduino.h"
#include "HumidityCO2Relay.h"
#include "Time.h"
#include <DHT.h>
#include <DHT_U.h>
#include <math.h>

HumidityCO2Relay::HumidityCO2Relay(int pinDHT, int pinRelay, int threshold): _dht(pinDHT, DHT11, 6)
{
  _pinRelay = pinRelay;
  _pinDHT = pinDHT;
  _debug = false;
  _tolerance = 5;
  _humidityThreshold = threshold;
  _thick = 5000;
  _startTime = millis();
}

String HumidityCO2Relay::getTemperature() {
  if(isnan(_temperature)) {
    return "-";
  }
  return String(_temperature);
}

int HumidityCO2Relay::getHumidityThreshold() {
  return _humidityThreshold;
}

String HumidityCO2Relay::getHumidity() {
  if(isnan(_humidity)) {
    return "-";
  }
  return String(_humidity);
}

void HumidityCO2Relay::setUp(bool debug) {
  _debug = debug;
  pinMode(_pinRelay, OUTPUT);
  if(_debug) {
    Serial.println("HumidityCO2Relay: DHT pin ("+String(_pinDHT)+"), Relay pin ("+String(_pinRelay)+")");
  }
  calculateToleranceValue();
}

void HumidityCO2Relay::activateFans(bool activate) {
  if(_debug) {
    Serial.println("Temperature: "+String(_temperature)+", Humidity: "+_humidity);
    Serial.print("Fan status: ");
  }
  if(activate) {
    digitalWrite(_pinRelay, HIGH);
    if(_debug) {
      Serial.println("ACTIVE");
    }
  } else {
    digitalWrite(_pinRelay, LOW);
    if(_debug) {
      Serial.println("NOT ACTIVE");
    }
  }
}

void HumidityCO2Relay::setHumidityThreshold(int threshold) {
  _humidityThreshold = threshold;
  calculateToleranceValue();
}

void HumidityCO2Relay::readTemperatureAndHumidity() {
  sensors_event_t event;
  _dht.temperature().getEvent(&event);

  _temperature = event.temperature;

  // Get temperature event and print its value.
  _dht.humidity().getEvent(&event);

  _humidity = event.relative_humidity;

  if(_debug) {
    Serial.println("Temperature: "+String(_temperature)+", Humidity: "+_humidity);
    Serial.println("Threshold: "+String(_humidityThreshold)+", Tolerance: "+_toleranceValue);
  }
}

void HumidityCO2Relay::calculateToleranceValue() {
  _toleranceValue = (static_cast<double>(_humidityThreshold) / 100 ) * static_cast<double>(_tolerance);
}

void HumidityCO2Relay::updateStatus() {

  if(millis() > _thick && (millis() - _thick) > _startTime) {
    _startTime = millis();
    readTemperatureAndHumidity();
    if(_humidity > (_humidityThreshold + 5)) {
      activateFans(true);
    } else {
      if (_humidity < (_humidityThreshold - 5)) {
        activateFans(false);
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

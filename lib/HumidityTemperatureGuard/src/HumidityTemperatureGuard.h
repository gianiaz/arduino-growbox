#include "Arduino.h"
#include <DHT.h>
#include <DHT_U.h>
#ifndef HumidityTemperatureGuard_h
#define HumidityTemperatureGuard_h

class HumidityTemperatureGuard
{
  public:
    HumidityTemperatureGuard(int pinDHT, int pinFan, int pinHumidifier, int fanThreshold, int humidifierThreshold);
    void setUp(bool debug);
    void updateStatus();
    void setFanThreshold(int threshold);
    void setHumidifierThreshold(int threshold);
    String getTemperature();
    String getHumidity();
    int getFanThreshold();
    int getHumidifierThreshold();
    String getHumidifierStatus();
    String getFanStatus();
  private:
    void activateFans(bool activate);
    void activateHumidifier(bool activate);
    void readTemperatureAndHumidity();
    int _fanStatus;
    int _humidifierStatus;
    int _pinDHT;
    int _pinFan;
    int _pinHumidifier;
    bool _debug;
    DHT_Unified _dht;
    float _temperature;
    float _humidity;
    int _fanThreshold;
    int _humidifierThreshold;
    int _tolerance;
    int _toleranceValue;
    long double _thick;
    long double _startTime;

};
#endif

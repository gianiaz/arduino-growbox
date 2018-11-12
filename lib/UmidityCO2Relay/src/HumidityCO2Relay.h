#include "Arduino.h"
#include <DHT.h>
#include <DHT_U.h>
#ifndef HumidityCO2Relay_h
#define HumidityCO2Relay_h

class HumidityCO2Relay
{
  public:
    HumidityCO2Relay(int pinDHT, int pinRelay, int threshold);
    void setUp(bool debug);
    void updateStatus();
    void setHumidityThreshold(int threshold);
    String getTemperature();
    String getHumidity();
    int getHumidityThreshold();
  private:
    void activateFans(bool activate);
    void readTemperatureAndHumidity();
    void calculateToleranceValue();
    int _pinDHT;
    int _pinRelay;
    bool _debug;
    DHT_Unified _dht;
    double _temperature;
    double _humidity;
    int _humidityThreshold;
    int _tolerance;
    int _toleranceValue;
    int _thick;
    int _startTime;

};
#endif

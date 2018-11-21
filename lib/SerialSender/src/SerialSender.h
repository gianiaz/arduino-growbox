#include "Arduino.h"

#ifndef SerialSender_h
#define SerialSender_h
class SerialSender
{
  public:
    SerialSender(int baudRate, long double updateTimeout);
    void setUp(bool debug);
    bool updateStatus(String data);
  private:
    long double _updateTimeout;
    int _baudRate;
    bool _debug;
    long double _lastOperation;
};
#endif

#include "Arduino.h"
#include "Servo.h"
#ifndef DayNight_h
#define DayNight_h

class DayNight
{
  public:
    DayNight(int pinServo, unsigned char pinPhotoResistor, unsigned char pinRelay, int threshold, unsigned long bounce);
    void updateStatus();
    void setPosition(int position);
    String isDay();
    void setUp(bool active, bool debug);
  private:
    int _pinServo;
    unsigned char _pinPhotoResistor;
    unsigned char _pinRelay;
    Servo _servo;
    int _millis;
    unsigned long _bounce;
    unsigned long _lastLecture;
    String _status;
    int _threshold;
    int _debug;
    int _pinPhotoResistorLecture;
    bool _active;
    void readPhotoResistor();
    void night();
    void day();
};
#endif

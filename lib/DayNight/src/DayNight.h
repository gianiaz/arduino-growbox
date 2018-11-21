#include "Arduino.h"
#include "Servo.h"
#ifndef DayNight_h
#define DayNight_h

class DayNight
{
  public:
    DayNight(int pinServo, unsigned char pinPhotoResistor, int threshold);
    void updateStatus();
    void setPosition(int position);
    void setDebug(bool debug);
    String isDay();
    void setUp();
  private:
    int _pinServo;
    unsigned char _pinPhotoResistor;
    Servo _servo;
    int _millis;
    String _status;
    int _threshold;
    int _debug;
    int _pinPhotoResistorLecture;
    void readPhotoResistor();
    void night();
    void day();
};
#endif

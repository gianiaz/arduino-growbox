#include "Arduino.h"
#include "Time.h"
#ifndef Hygrometer_h
#define Hygrometer_h

class Hygrometer
{
  public:
    Hygrometer(uint8_t pin, int secondsDelayBetwenLectures);
    void updateStatus();
    void setUp(bool active, bool debug);
    String getHumidity();
  private:
    bool _debug;
    uint8_t _pin;
    unsigned long _milliseconds_delay_betwen_lectures;
    unsigned long _last_lecture;
    unsigned long _last_lecture_time;
    void doRead();
    bool _active;
};

#endif

#include <Arduino.h>

#ifndef _METER_H_
#define _METER_H_

class meter{
  private:
    const int Meterpin;
    int Dirc = 10;
    float curpos = 0;
    void retrograde();
    
  public:
    meter(int meterpin);
    void trans(int dst);
    void stepforward();
};

#endif

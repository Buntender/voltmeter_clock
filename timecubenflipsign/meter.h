#include <Arduino.h>

#ifndef _METER_H_
#define _METER_H_

const bool AM = false, PM = true;

class meter{
  private:
    const int Meterpin, Signpos, Signneg;
    int Dirc = 10;
    float curpos = 0;
    bool curampm = AM;

    void retrograde(int dstampm);
    void signtrans(bool dst);
    void signstop();
    
  public:
    meter(int meterpin, int signpos, int signneg);
    void trans(int dst);
    void stepforward();
};

#endif

#include <Arduino.h>

#ifndef _METER_H_
#define _METER_H_

class meter{
  private:
    int Meterpin = -1;  
    float curpos = 0;
    void flyback();
    
  public:
    meter(int meterpin);
    void trans(int dst);
};

#endif

#include "meter.h"

void meter::retrograde(){
  analogWrite(Meterpin, 0); //指针先加速回落后减速
  delay(120);
  for(int i = 0; i <= 720; i+= 144){
    analogWrite(Meterpin, i);
    delay(1);
  }
  for(int i = 720; i >= 0; i-=90){
    analogWrite(Meterpin, i);
    delay(1);
  }
  analogWrite(Meterpin, 0);
}
   
meter::meter(int meterpin){
 analogWriteFreq(100);
 analogWriteRange(720);
 Meterpin = meterpin;
 analogWrite(Meterpin, curpos);
}

void meter::trans(int dst){
  if(curpos > 700 && dst < 20) retrograde();
  else{
    for(int i = 0; i < 100; i++){
      analogWrite(Meterpin, curpos + (dst - curpos) / 100.0 * i);
      delay(10);
    }
  }
  curpos = dst;
  analogWrite(Meterpin, curpos);
}

#include "meter.h"

void meter::flyback(){
  analogWrite(Meterpin, 0);
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

//      for(int i = 720; i >= 0; i-=8){
//      analogWrite(METER, i);
//      delay(1);
//  }  
}
   
meter::meter(int meterpin){
 analogWriteFreq(100);  /* Set PWM frequency to 50Hz */
 analogWriteRange(720);
 Meterpin = meterpin;
 analogWrite(Meterpin, curpos);
}

void meter::trans(int dst){
  if(curpos > 700 && dst < 20) flyback();
  else{
    for(int i = 0; i < 100; i++){
      analogWrite(Meterpin, curpos + (dst - curpos) / 100.0 * i);
      delay(5);
    }
  }
  curpos = dst;
  analogWrite(Meterpin, curpos);
}

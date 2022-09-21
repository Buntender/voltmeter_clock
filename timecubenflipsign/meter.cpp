#include "meter.h"

void meter::retrograde(int dstampm){
  signtrans(dstampm);
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
  delay(400);
  signstop();
}
   
meter::meter(int meterpin, int signpos, int signneg):Meterpin(meterpin), Signpos(signpos), Signneg(signneg){
 analogWriteFreq(100);
 analogWriteRange(720);
 pinMode(Signpos, OUTPUT);
 pinMode(Signneg, OUTPUT);
 signtrans(curampm);
 delay(500);
 signstop();
}

void meter::trans(int dst){
  bool dstampm = (dst >= 720);
  dst = dst % 720;
  if(curpos > 700 && dst < 20) retrograde(dstampm);
  else{
    for(int i = 0; i < 100; i++){
      analogWrite(Meterpin, curpos + (dst - curpos) / 100.0 * i);
      delay(10);
    }
  }
  
  if(curampm != dstampm){
    signtrans(dstampm);
    delay(500);
    signstop();
  }
  curpos = dst;
  analogWrite(Meterpin, curpos);
}

void meter::signtrans(bool dst){
  if(dst == AM){
    digitalWrite(Signpos, HIGH);
    digitalWrite(Signneg, LOW);
  }
  if(dst == PM){
    digitalWrite(Signpos, LOW);
    digitalWrite(Signneg, HIGH);
  }
  curampm = dst;
}

void meter::signstop(){
  digitalWrite(Signpos, LOW);
  digitalWrite(Signneg, LOW);
}

void meter::stepforward(){
  if(curpos > 718) Dirc = -10;
  if(curpos < 2) Dirc = 10;
  curpos += Dirc;
  analogWrite(Meterpin, curpos);
}

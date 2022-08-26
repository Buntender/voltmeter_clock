uint8_t METER = 0;

void setup(){
 analogWriteFreq(100);  /* Set PWM frequency to 50Hz */
 analogWriteRange(720);
 Serial.begin(115200);
}

void loop(){
  for(int i = 0; i <= 720; i+=2){
    analogWrite(METER, i);
    delay(1);
  }
  
  analogWrite(METER, 0);
  delay(120);
  for(int i = 0; i <= 720; i+= 144){
    analogWrite(METER, i);
    delay(1);
  }
  for(int i = 720; i >= 0; i-=90){
    analogWrite(METER, i);
    delay(1);
  }
  analogWrite(METER, 0);

//  for(int i = 720; i >= 0; i-=8){
//    analogWrite(METER, i);
//    delay(1);
//  }
  
  delay(4000);
}

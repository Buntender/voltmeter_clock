uint8_t METER = 12;

void setup(){
 analogWriteFreq(100);
 analogWriteRange(720);
 Serial.begin(115200);
}

void loop(){
  for(int i = 0; i <= 720; i+=2){
    analogWrite(METER, i);
    delay(1);
  }
  for(int i = 720; i >= 0; i-=2){
    analogWrite(METER, i);
    delay(1);
  }
}

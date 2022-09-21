#include <Arduino.h>

// time
#include <time.h>                       // time() ctime()
#include <sys/time.h>                   // struct timeval
#include <coredecls.h>                  // settimeofday_cb()

#include "wificonnect.h"
#include "meter.h"

#include "Ticker.h"

/***************************
 * Begin Settings
 **************************/

#define TZ              8       // (utc+) TZ in hours
#define DST_MN          0      // use 60mn for summer time in some countries

/***************************
 * End Settings
 **************************/

#define TZ_MN           ((TZ)*60)
#define TZ_SEC          ((TZ)*3600)
#define DST_SEC         ((DST_MN)*60)

#define VALIDTIME(TIME) (TIME > 1576800000)
#define GETINVALIDTIME(TIME) (TIME - 1576800000)

long timeSinceLastWUpdate = 0;
long timeSinceLastCurrUpdate = 0;

uint8_t METER_PIN = 4, SIGN_POS = 15, SIGN_NEG = 13;
meter* mymeter;

int getLocalTime()
{
  time_t now;
  time(&now);
  struct tm * timeinfo;
  timeinfo = localtime(&now);
  Serial.print(timeinfo->tm_hour);
  Serial.print(":");
  Serial.println(timeinfo->tm_min);
  return timeinfo->tm_hour * 60 + timeinfo->tm_min;
}

void setup() {
  Serial.begin(115200);
  mymeter = new meter(METER_PIN, SIGN_POS, SIGN_NEG);
  
  auto stepforwardwrapper = []() -> void {mymeter->stepforward();};
  Ticker scanpin;
  scanpin.attach_ms(20, stepforwardwrapper);

  while(!VALIDTIME(time(nullptr))){
    WiFi.mode(WIFI_OFF);
    if(lastConfig() == false){
      htmlConfig();//HTML配网
    }
    Serial.println("");
    configTime(TZ_SEC, DST_SEC, "pool.ntp.org","0.cn.pool.ntp.org","1.cn.pool.ntp.org");
    for(int timeout = 600; timeout > 0; timeout--){
        if(VALIDTIME(time(nullptr))) break;
        delay(500);
        Serial.print(".");
    }
  }
  
  WiFi.forceSleepBegin(); // Wifi off
}

void loop() {
  static int reliability = 28;
  int curtime = getLocalTime();
  mymeter->trans(curtime);
  if (curtime % 360 <= 355 && curtime % 360 >= 354) {
    WiFi.forceSleepWake(); // Wifi on
    yield();
    lastConfig();
    if(VALIDTIME(time(nullptr))){
      time_t rtc = GETINVALIDTIME(time(nullptr));
      timeval tv = { rtc, 0 };
      settimeofday(&tv, nullptr);
    }
    
    configTime(TZ_SEC, DST_SEC, "pool.ntp.org","0.cn.pool.ntp.org","1.cn.pool.ntp.org");
    for(int timeout = 600; timeout > 0; timeout--){
        if(VALIDTIME(time(nullptr))) break;
        delay(500);
        Serial.print(".");
    }
    if(!VALIDTIME(time(nullptr))) reliability--;
    else reliability = 28;
    if(reliability <= 0) ESP.restart();
    WiFi.forceSleepBegin(); // Wifi off
  }
  if (curtime % 720 < 718) delay(60 * 1000);
  else delay(1000);
}

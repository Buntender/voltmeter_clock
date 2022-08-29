#include <Arduino.h>

// time
#include <time.h>                       // time() ctime()
#include <sys/time.h>                   // struct timeval
#include <coredecls.h>                  // settimeofday_cb()

#include "wificonnect.h"
#include "meter.h"

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

long timeSinceLastWUpdate = 0;
long timeSinceLastCurrUpdate = 0;

uint8_t METER_PIN = 12;
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
  mymeter = new meter(METER_PIN);
  if(lastConfig() == false){
      htmlConfig();//HTML配网
  }
  Serial.println("");
  configTime(TZ_SEC, DST_SEC, "pool.ntp.org","0.cn.pool.ntp.org","1.cn.pool.ntp.org");
  for(int timeout = 300; timeout > 0; timeout--){
      if(time(nullptr) >= 1510592825) break;
      delay(100);
      Serial.print(".");
  }
  WiFi.forceSleepBegin(); // Wifi off
}

void loop() {
  int curtime = getLocalTime();
  mymeter->trans(curtime % 720);
  if (curtime % 60 <= 55 && curtime % 60 >= 54) {
    WiFi.forceSleepWake(); // Wifi on
    yield();
    lastConfig();
    configTime(TZ_SEC, DST_SEC, "pool.ntp.org","0.cn.pool.ntp.org","1.cn.pool.ntp.org");
    delay(60 * 1000);
    WiFi.forceSleepBegin(); // Wifi off
  }
  if (curtime % 720 < 718) delay(60 * 1000);
  else delay(1000);
}

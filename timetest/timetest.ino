#include <Arduino.h>

// time
#include <time.h>                       // time() ctime()
#include <sys/time.h>                   // struct timeval
#include <coredecls.h>                  // settimeofday_cb()

#include "wificonnect.h"

/***************************
 * Begin Settings
 **************************/

#define TZ              8       // (utc+) TZ in hours
#define DST_MN          0      // use 60mn for summer time in some countries

// Setup
//const int UPDATE_INTERVAL_SECS = 20 * 60; // Update every 20 minutes  online weather
const int UPDATE_INTERVAL_SECS = 2; // Update every 20 minutes  online weather

/***************************
 * End Settings
 **************************/

#define TZ_MN           ((TZ)*60)
#define TZ_SEC          ((TZ)*3600)
#define DST_SEC         ((DST_MN)*60)

time_t now;

long timeSinceLastWUpdate = 0;
long timeSinceLastCurrUpdate = 0;

void printLocalTime()
{
  time_t now;
  struct tm * timeinfo;
  time(&now);
  timeinfo = localtime(&now);  
  Serial.print(timeinfo->tm_hour);
  Serial.print(":");
  Serial.print(timeinfo->tm_min);
  Serial.print(":");
  Serial.println(timeinfo->tm_sec);
}

void setup() {
  Serial.begin(115200);
  if(autoConfig() == false){
      htmlConfig();//HTML配网
  }
  Serial.println("");
  configTime(TZ_SEC, DST_SEC, "pool.ntp.org","0.cn.pool.ntp.org","1.cn.pool.ntp.org");
}

void loop() {
  if (millis() - timeSinceLastWUpdate > (1000L*UPDATE_INTERVAL_SECS)) {
    timeSinceLastWUpdate = millis();
    printLocalTime();
  }
}

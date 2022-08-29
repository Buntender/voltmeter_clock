#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "savenet.h"

#ifndef _WIFICONNECT_H_
#define _WIFICONNECT_H_

bool lastConfig();
void handleRoot();
void HandleScanWifi();
void HandleWifi();
void handleNotFound();
void htmlConfig();

#endif

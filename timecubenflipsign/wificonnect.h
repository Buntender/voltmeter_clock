/**The MIT License (MIT)

Copyright (c) 2018 by Daniel Eichhorn - ThingPulse

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

See more at https://thingpulse.com
*/

//Monsteryuan forked from Daniel Eichhorn/ThingPulse ESP8266 Weather Station

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "savenet.h"

#ifndef _WIFICONNECT_H_
#define _WIFICONNECT_H_

const String HTML_TITLE = "<!DOCTYPE html><html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\"><title>ESP8266网页配网</title>";
const String HTML_SCRIPT_ONE = "<script type=\"text/javascript\">function wifi(){var ssid = s.value;var password = p.value;var xmlhttp=new XMLHttpRequest();xmlhttp.open(\"GET\",\"/HandleWifi?ssid=\"+ssid+\"&password=\"+password,true);xmlhttp.send();xmlhttp.onload = function(e){alert(this.responseText);}}</script>";
const String HTML_SCRIPT_TWO = "<script>function c(l){document.getElementById('s').value=l.innerText||l.textContent;document.getElementById('p').focus();}</script>";
const String HTML_HEAD_BODY_BEGIN = "</head><body>请输入wifi信息进行配网:";
const String HTML_FORM_ONE = "<form>WiFi名称：<input id='s' name='s' type=\"text\" placeholder=\"请输入您WiFi的名称\"><br>WiFi密码：<input id='p' name='p' type=\"text\" placeholder=\"请输入您WiFi的密码\"><br><input type=\"button\" value=\"扫描\" onclick=\"window.location.href = '/HandleScanWifi'\"><input type=\"button\" value=\"连接\" onclick=\"wifi()\"></form>";
const String HTML_BODY_HTML_END = "</body></html>";

bool lastConfig();
void handleRoot();
void HandleScanWifi();
void HandleWifi();
void handleNotFound();
void htmlConfig();

#endif

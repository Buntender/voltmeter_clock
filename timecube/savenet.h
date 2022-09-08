#include <EEPROM.h>

#ifndef _SAVENET_H_
#define _SAVENET_H_

#define EEPROM_START 1024

struct WifiPwd {
  char ssid[32];
  char pwd[64];
};

void saveConfig(WifiPwd *wifipwd); //保存参数到eeprom
WifiPwd* loadConfigs(); //获取wifi账号密码信息
void clearConfig(); //清空wifi账号和密码

#endif

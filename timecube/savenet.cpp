#include "savenet.h"

void saveConfig(WifiPwd *wifipwd) {
  EEPROM.begin(EEPROM_START);
  uint8_t *p = (uint8_t*)(wifipwd);
  for (int i = 0; i < sizeof(*wifipwd); i++) {
    EEPROM.write(i, *(p + i));
  }
  EEPROM.commit();
  // 释放内存
  delete wifipwd;
}

WifiPwd* loadConfigs() {
  // 为变量请求内存
  WifiPwd *pvalue  = new WifiPwd;   
  EEPROM.begin(EEPROM_START);
  uint8_t *p = (uint8_t*)(pvalue);
  for (int i = 0; i < sizeof(*pvalue); i++) {
    *(p + i) = EEPROM.read(i);
  }
  EEPROM.commit();
  return pvalue;
}

void clearConfig() {
  EEPROM.begin(EEPROM_START);
  // 这里为啥是96 ，因为在结构体声明的长度之和就是96
  for (int i = 0; i < 96; i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();
}

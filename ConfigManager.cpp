#include "ConfigManager.h"
#include <EEPROM.h>

ConfigManager::cfgstruct cfg;
int ConfigManager::eeSize;

ConfigManager::ConfigManager(int esize){
  eeSize = esize;
}

void ConfigManager::saveConfig(){
  EEPROM.begin(4095);
  EEPROM.put(0, cfg);
  // delay(200);
  EEPROM.commit();
  EEPROM.end();
}

void ConfigManager::loadConfig(){
  EEPROM.begin(4095);
  EEPROM.get( 0, cfg);
  EEPROM.end();
}

void ConfigManager::deleteConfig(){
  EEPROM.begin(4095);
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.end();
}

bool ConfigManager::firstData(){
  int n = sizeof(cfg.ver) / sizeof(cfg.ver[0]);
  if(n == 0) {
    strcpy(cfg.ver, "V01");
    strcpy(cfg.wifissid, "");
    strcpy(cfg.wifiuser, "");
    strcpy(cfg.wifipass, "");
    strcpy(cfg.wifihost, "");
    strcpy(cfg.esptitle, "ESP8266");
    return true;
  }
  return false;
}

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
  EEPROM.commit();
  EEPROM.end();
}

void ConfigManager::loadConfig(){
  ConfigManager cfg;
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

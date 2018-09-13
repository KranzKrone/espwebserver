#include "ConfigManager.h"
#include <EEPROM.h>

ConfigManager::cfgstruct cfg;

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

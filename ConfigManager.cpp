#include "ConfigManager.h"
#include <EEPROM.h>
#include "Arduino.h"

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
  Serial.print("Version des Speichers ist: ");
  Serial.println(cfg.versio);
  
  if(cfg.versio != SVERSION) {
    /*
     * Braucht man nicht wirklich.
    Serial.println("Speicher: wird gelöscht.");
    this->deleteConfig();
    Serial.println("Speicher: wurde gelöscht.");
    */
    cfg.versio = SVERSION;
    strcpy(cfg.wifissid1, "");
    strcpy(cfg.wifiuser1, "");
    strcpy(cfg.wifipass1, "");
    strcpy(cfg.wifissid2, "");
    strcpy(cfg.wifiuser2, "");
    strcpy(cfg.wifipass2, "");
    strcpy(cfg.wifihost, "");
    strcpy(cfg.esptitle, "ESP8266");
    strcpy(cfg.mqtt_server, "");
    strcpy(cfg.mqtt_topic, "");
    strcpy(cfg.webhook_url, "");
    strcpy(cfg.webhook_fp, "");
    return true;
  }
  return false;
}

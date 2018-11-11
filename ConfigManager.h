#ifndef ConfigManager_h
#define ConfigManager_h

#include <EEPROM.h>
// #include <stdlib.h>

class ConfigManager {

  public :
    // The dataobject to save data
    struct cfgstruct
    {
      int versio;
      char wifissid[32];
      char wifiuser[36];
      char wifipass[64];
      char wifihost[24];
      char esptitle[18];
      char mqtt_server[124];
      char mqtt_topic[64];
      char webhook_url[124];
      char webhook_fp[64];
    };

    // Config DBO
    cfgstruct cfg;
    static int eeSize;
    // init with EEPROM Size
    ConfigManager(int esize=4095); 
    // get config data from eeprom 
    void loadConfig();
    // save (update) config data
    void saveConfig();
    // löschen des Speicher
    void deleteConfig();
    // setzen wenn der Speicher null
    bool firstData(); 
};

#endif  

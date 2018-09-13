#include <EEPROM.h>
#include <stdlib.h>

class ConfigManager {

  public :
    // The dataobject to save data
    struct cfgstruct
    {
      char wifissid[32];
      char wifiuser[36];
      char wifipass[64];
      char wifihost[24]; 
    };
    cfgstruct cfg; 
    // get config data from eeprom 
    void loadConfig();
    // save (update) config data
    void saveConfig();
    // löschen des Speicher
    void deleteConfig(); 
};
  

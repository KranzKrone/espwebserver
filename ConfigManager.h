#include <EEPROM.h>
#include <stdlib.h>

struct configuration_type
{
  char vnr[6]; // place to detect if settings actually are written
  char wifissid[32];
  char wifiuser[36];
  char wifipass[64];
  char wifihost[24]; 
};

class EEPROMManager {
  public : 
    static const char ver[6]; 
    void loadConfig();
    void saveConfig();
    
    void deleteConfig(){
      for (int i = 0 ; i < EEPROM.length() ; i++) {
        if(EEPROM.read(i) != 0)                     
        {
          EEPROM.write(i, 0);
        }
      }
      // Serial.println("EEPROM erased");  
    }; 
};
  

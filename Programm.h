#ifndef Programm_h
#define Programm_h

#include <WString.h>
#include "ConfigManager.h"
#include "DS18B20.h"

class Programm {

  public:
  
    int pdrehzahl = 0;
    int pdelayms = 0;
    String prange = "0";
    String prms = "0";

    ConfigManager* pconfigmanager;
    DS18B20* pds18b20;

    Programm(ConfigManager*_cm, DS18B20*_ds18b20);
};

#endif

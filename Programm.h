#ifndef Programm_h
#define Programm_h

#include <WString.h>
#include "ConfigManager.h"

class Programm {

  public:
  
    int pdrehzahl;
    int pdelayms;
    String prange;
    String prms;

    ConfigManager* pconfigmanager;

    Programm(ConfigManager*_cm);
};

#endif

#ifndef Programm_h
#define Programm_h

#include "Arduino.h"
#include "ConfigManager.h"
#include "DS18B20.h"

#define P13LED 13
#define P12RELAY 12 

class Programm {

  public:
  
    int pdrehzahl = 0;
    int pdelayms = 0;
    String prange = "0";
    String prms = "0";

    // Marker für die Steckdose SONOFF S20
    bool ponoff = false;
    
    ConfigManager* pconfigmanager;
    DS18B20* pds18b20;

    Programm(ConfigManager*_cm, DS18B20*_ds18b20);
    void startup();
    // Sonoff S20 mache ich hier an oder aus. Die Lampe und das Relais hängen noch zusammen.
    void s20_switch();
    
    /**
     * Funktion für das Versenden von Wetterdaten an einen Server.
     * 
     * see https://de.wikibooks.org/wiki/C%2B%2B-Programmierung:_Ausdr%C3%BCcke_und_Operatoren
     */
    void sendTempData();
};

#endif

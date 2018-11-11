#ifndef WebHook_h
#define WebHook_h
#include <Arduino.h>
#include "Programm.h"

class WebHook {
  
  public:
    Programm* programm;
    WebHook(Programm*_programm);
    int sendUrlQuery(String _urlQuery);
    
    // Diese Funtkion funktioniert, sollte aber nur bedingt genutzt werden. TODO: Weiteres testen der Funktionen.
    static int httpsGetAsyc(String _url, String _publicKey); 
};

#endif

#ifndef ServerManager_h
#define ServerManager_h

#include "Programm.h"
#include <ESP8266WebServer.h>

#define XMLBEGIN "<?xml version=\"1.0\" encoding=\"UTF-8\"?><?xml-stylesheet type=\"text/xsl\" href=\"/design.xsl\"?><root><head><title>ESP8266 - Websever</title><esptitle>Steckdose :: Küche</esptitle></head>"
#define XMLEND "</root>"
/**
 * DE: Der ServerManager arbeitet wie eine View und ist das auf das Programm-Object über einen Zeiger miteinander verbunden.
 */
class ServerManager {
  
  public:
    
    Programm* programm;
    
    ESP8266WebServer* server;

    ServerManager(Programm*_programm);

    void serverLoop();
};

#endif

#ifndef ServerManager_h
#define ServerManager_h

#include "Programm.h"
#include <ESP8266WebServer.h>

#define XMLHEADER "<?xml version=\"1.0\" encoding=\"UTF-8\"?><?xml-stylesheet type=\"text/xsl\" href=\"/design.xsl\"?>"
/**
 * DE: Der ServerManager arbeitet wie eine View und ist das auf das Programm-Object über einen Zeiger miteinander verbunden.
 */
class ServerManager {
  
  public:

    struct ServerOutput {
      int so_code = 202;
      String so_type = "text/xml";
      String so_title = "ESP8266 Webserver";
      String so_msg = "";
      String so_content = "<startpage />";
    };
    
    Programm* programm;
    
    ESP8266WebServer* server;

    ServerManager(Programm*_programm);

    void serverLoop();
  
  private:

    void sendServer(ServerOutput _so);
};

#endif

#include "ServerManager.h"
#include <ESP8266WebServer.h>

ServerManager::ServerManager(Programm*_programm){
  programm = _programm;
  server = new ESP8266WebServer(80);

  // Hier werden die einzelnen Serverfunktionen hinzugefügt.
  server->on("/", [=]() {
    Serial.println("Startpage");
    server->send(200, "text/html", "Dies ist ein Testtext");
  });

  server->onNotFound([=]() {
    server->send(404, "text/html", "404: Not Found");
  });
  
  server->begin();
}

void ServerManager::serverLoop(){
  server->handleClient();
}

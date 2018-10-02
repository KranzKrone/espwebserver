#include "ServerManager.h"
#include <ESP8266WebServer.h>
#include <FS.h>

ServerManager::ServerManager(Programm*_programm){
  programm = _programm;

  Serial.println( (!SPIFFS.begin()) ? "SPIFFS Mount failed" : "SPIFFS Mount succesfull");
  
  server = new ESP8266WebServer(80);
  
  server->serveStatic("/materialize.min.css", SPIFFS, "/materialize.min.css", "max-age=7200");
  server->serveStatic("/materialize.min.js", SPIFFS, "/materialize.min.js", "max-age=7200");
  server->serveStatic("/design.xsl", SPIFFS, "/design.xsl", "max-age=7200");

  // Hier werden die einzelnen Serverfunktionen hinzugefügt.
  
  server->on("/", [=]() {
    Serial.println("Startpage");
    String output = XMLBEGIN "<startpage>";
    output += "</startpage>" XMLEND;
    server->send(200, "text/xml", output);
  });

  
  server->on("/steckdose/", [=]() {
    Serial.println("Steckdose");
    String output = XMLBEGIN "<steckdose>";
    output += "</steckdose>" XMLEND;
    server->send(200, "text/xml", output);
  });
  
  // Hier werden die Seiten im Server definiert.
  server->on("/settings/", [=]() {

    // Konfiguarartion wird hier gespeichert.
    if(server->hasArg("save_eeprom")){
      (server->hasArg("wid")) ? strcpy(programm->pconfigmanager->cfg.wifissid, server->arg("wid").c_str() )  : "";
      (server->hasArg("wuser")) ? strcpy(programm->pconfigmanager->cfg.wifiuser, server->arg("wuser").c_str() ) : "";
      (server->hasArg("wpw")) ? strcpy(programm->pconfigmanager->cfg.wifipass, server->arg("wpw").c_str() ) : "";
      (server->hasArg("hostname")) ? strcpy(programm->pconfigmanager->cfg.wifihost, server->arg("hostname").c_str() ) : "";
      (server->hasArg("esptitle")) ? strcpy(programm->pconfigmanager->cfg.esptitle, server->arg("esptitle").c_str() ) : "";
      programm->pconfigmanager->saveConfig();
      Serial.println("Konfiguration im EEPROM gespeichert.");
    } 

    // Konfiguration wird hier gelöscht.
    if(server->hasArg("del_eeprom")) {
      programm->pconfigmanager->deleteConfig();
      Serial.println("Konfiguration wurde gelöscht.");
    }
    
    Serial.println("Startup");
    String output = XMLBEGIN "<settings>";
    output += "<wid>" + String(programm->pconfigmanager->cfg.wifissid) + "</wid>";
    output += "<wuser>" + String(programm->pconfigmanager->cfg.wifiuser) + "</wuser>";
    output += "<wpw>" + String(programm->pconfigmanager->cfg.wifipass) + "</wpw>";
    output += "<hostname>" + String(programm->pconfigmanager->cfg.wifihost) + "</hostname>";
    output += "<esptitle>" + String(programm->pconfigmanager->cfg.esptitle) + "</esptitle>";
    output += "</settings>" XMLEND;
    
    server->send(200, "text/xml", output);
  });

  server->on("/temperatur/", [=]() {
    Serial.println("Temperatur XML");
    String output = XMLBEGIN "<temperatur>";
    output += "<aussentemperatur>" + programm->pds18b20->getDS18B20Celsius(0) + "</aussentemperatur>";
    output += "<innentemperatur>" + programm->pds18b20->getDS18B20Celsius(1) + "</innentemperatur>";
    output += "</temperatur>" XMLEND;
    server->send(200, "text/xml", output);
  });
  
  server->on("/vibrator/", [=]() {
    
    programm->prange = (server->hasArg("range")) ? server->arg("range") : programm->prange;
    programm->pdrehzahl = programm->prange.toInt() * 10;
    
    programm->prms = (server->hasArg("rms")) ? server->arg("rms") : programm->prms;
    programm->pdelayms = programm->prms.toInt() * 300;
    
    String output = XMLBEGIN "<vibrator><range>" + programm->prange + "</range><rms>" + programm->prms + "</rms></vibrator>" XMLEND;
    server->send(200, "text/xml", output);
    yield();
  });

  server->onNotFound([=]() {
    server->send(404, "text/html", "404: Not Found");
  });
  
  server->begin();
}

void ServerManager::serverLoop(){
  server->handleClient();
}

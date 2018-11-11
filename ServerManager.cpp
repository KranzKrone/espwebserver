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
    Serial.println("Startpage, Inhalte werden aus dem Struct ServerOutput geladen.");
    ServerOutput so;
    sendServer(so);
  });

  server->on("/steckdose/", [=]() {
    Serial.println("Steckdose");
    // Ändern der Steckdose
    
    if(server->hasArg("s20")){
      Serial.println("s20 wurde gesetzt");
      programm->s20_switch();
    }
    
    ServerOutput so;
    so.so_content = "<steckdose />" ;
    sendServer(so);
  });
  
  // Hier werden die Seiten im Server definiert.
  server->on("/settings/", [=]() {

    ServerOutput so;
    
    // Konfiguarartion wird hier gespeichert.
    if(server->hasArg("save_eeprom")){
      (server->hasArg("wid")) ? strcpy(programm->pconfigmanager->cfg.wifissid, server->arg("wid").c_str() )  : 0;
      (server->hasArg("wuser")) ? strcpy(programm->pconfigmanager->cfg.wifiuser, server->arg("wuser").c_str() ) : 0;
      (server->hasArg("wpw")) ? strcpy(programm->pconfigmanager->cfg.wifipass, server->arg("wpw").c_str() ) : 0;
      (server->hasArg("hostname")) ? strcpy(programm->pconfigmanager->cfg.wifihost, server->arg("hostname").c_str() ) : 0;
      (server->hasArg("esptitle")) ? strcpy(programm->pconfigmanager->cfg.esptitle, server->arg("esptitle").c_str() ) : 0;
      // MQTT
      (server->hasArg("mqtt_broker")) ? strcpy(programm->pconfigmanager->cfg.mqtt_server, server->arg("mqtt_broker").c_str() ) : 0;
      (server->hasArg("mqtt_topic")) ? strcpy(programm->pconfigmanager->cfg.mqtt_topic, server->arg("mqtt_topic").c_str() ) : 0;
      // WebHook
      (server->hasArg("wh_url")) ? strcpy(programm->pconfigmanager->cfg.webhook_url, server->arg("wh_url").c_str() ) : 0;
      (server->hasArg("wh_fp")) ? strcpy(programm->pconfigmanager->cfg.webhook_fp, server->arg("wh_fp").c_str() ) : 0;
      programm->pconfigmanager->saveConfig();
      Serial.println("Konfiguration im EEPROM gespeichert.");
    } 

    // Konfiguration wird hier gelöscht.
    if(server->hasArg("del_eeprom")) {
      programm->pconfigmanager->deleteConfig();
      Serial.println("Konfiguration wurde gelöscht.");
    }
 
    String output =  "<settings>";
    output += "<wid>" + String(programm->pconfigmanager->cfg.wifissid) + "</wid>";
    output += "<wuser>" + String(programm->pconfigmanager->cfg.wifiuser) + "</wuser>";
    output += "<wpw>" + String(programm->pconfigmanager->cfg.wifipass) + "</wpw>";
    output += "<hostname>" + String(programm->pconfigmanager->cfg.wifihost) + "</hostname>";
    output += "<esptitle>" + String(programm->pconfigmanager->cfg.esptitle) + "</esptitle>";
    // MQTT
    output += "<mqtt_server>" + String(programm->pconfigmanager->cfg.mqtt_server) + "</mqtt_server>";
    output += "<mqtt_topic>" + String(programm->pconfigmanager->cfg.mqtt_topic) + "</mqtt_topic>";
    // WebHook
    output += "<wh_url>" + String(programm->pconfigmanager->cfg.webhook_url) + "</wh_url>";
    output += "<wh_fp>" + String(programm->pconfigmanager->cfg.webhook_fp) + "</wh_fp>";
    output += "</settings>";
    
    so.so_content = output;
    sendServer(so);
  });

  server->on("/temperatur/", [=]() {
    ServerOutput so;
    String output =  "<temperatur>";
    output += "<aussentemperatur>" + programm->pds18b20->getDS18B20Celsius(0) + "</aussentemperatur>";
    output += "<innentemperatur>" + programm->pds18b20->getDS18B20Celsius(1) + "</innentemperatur>";
    output += "</temperatur>";
    so.so_content = output;
    sendServer(so);
  });
  
  server->on("/vibrator/", [=]() {
    
    programm->prange = (server->hasArg("range")) ? server->arg("range") : programm->prange;
    programm->pdrehzahl = programm->prange.toInt() * 10;
    
    programm->prms = (server->hasArg("rms")) ? server->arg("rms") : programm->prms;
    programm->pdelayms = programm->prms.toInt() * 300;

    ServerOutput so;
    so.so_content =  "<vibrator><range>" + programm->prange + "</range><rms>" + programm->prms + "</rms></vibrator>";
    sendServer(so);
  });

  server->onNotFound([=]() {
    ServerOutput so;
    so.so_code = 404;
    so.so_content =  "<err />" ;
    sendServer(so);
  });
  
  server->begin();
}

void ServerManager::sendServer(ServerManager::ServerOutput _so){
  String oc = XMLHEADER "<root><head>";
  // Globale Inhalte für den Head-Bereich - global part for Headbereich
  oc += "<esptitle>" + String(this->programm->pconfigmanager->cfg.esptitle) + "</esptitle>";
  oc += "</head>" + _so.so_content + "</root>";
  this->server->send(_so.so_code, _so.so_type, oc);
  yield();
}

void ServerManager::serverLoop(){
  server->handleClient();
}

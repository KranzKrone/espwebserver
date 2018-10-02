/**
 * Sketch for ESP Webserver, usefull for different projects.
 * 
 * @author Stefan Krone
 * @version 0.0.0
 */

#include <OneWire.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include "ConfigManager.h"
#include "WiFiManager.h"
#include "DS18B20.h"
#include "Programm.h"

#define XMLBEGIN "<?xml version=\"1.0\" encoding=\"UTF-8\"?><?xml-stylesheet type=\"text/xsl\" href=\"/design.xsl\"?><root><head><title>ESP8266 - Websever</title><esptitle>Steckdose :: Küche</esptitle></head>"
#define XMLEND "</root>"
#define MOTOR 4

#define ONE_WIRE_BUS 5

// Objects for the programm
ConfigManager conman;
WiFiManager wman;
OneWire oneWire(ONE_WIRE_BUS);
DS18B20 sensoren(&oneWire);
ESP8266WebServer server(80);
// Im Programm speichere ich die Veriablen für die Bewegungen und andere Dinge
Programm programm(&conman, &sensoren);

/**
 * DE: Initialisierung des Programms
 * EN: Programm is init here
 */
void setup() {
 
  Serial.begin(115200);
  delay(200);
  Serial.setDebugOutput(false);
  
  Serial.println( (!SPIFFS.begin()) ? "SPIFFS Mount failed" : "SPIFFS Mount succesfull");
  Serial.println("Webserver wird gestartet!");

  // Die Konfiguration lade ich hier.
  conman.loadConfig();
  // Hier wird WLan gestartet.
  wman.begin(conman.cfg.wifissid, conman.cfg.wifipass, conman.cfg.wifihost, "ESPDEV", "");
  
  // Statische Dateien wie CSS, JS wird geladen.
  server.serveStatic("/materialize.min.css", SPIFFS, "/materialize.min.css", "max-age=7200");
  server.serveStatic("/materialize.min.js", SPIFFS, "/materialize.min.js", "max-age=7200");
  server.serveStatic("/design.xsl", SPIFFS, "/design.xsl", "max-age=7200");

  server.on("/", []() {
    Serial.println("Startpage");
    String output = XMLBEGIN "<startpage>";
    output += "</startpage>" XMLEND;
    server.send(200, "text/xml", output);
  });

  server.on("/steckdose/", []() {
    Serial.println("Steckdose");
    String output = XMLBEGIN "<steckdose>";
    output += "</steckdose>" XMLEND;
    server.send(200, "text/xml", output);
  });
  
  // Hier werden die Seiten im Server definiert.
  server.on("/settings/", []() {

    // Konfiguarartion wird hier gespeichert.
    if(server.hasArg("save_eeprom")){
      (server.hasArg("wid")) ? strcpy(conman.cfg.wifissid, server.arg("wid").c_str() )  : "";
      (server.hasArg("wuser")) ? strcpy(conman.cfg.wifiuser, server.arg("wuser").c_str() ) : "";
      (server.hasArg("wpw")) ? strcpy(conman.cfg.wifipass, server.arg("wpw").c_str() ) : "";
      (server.hasArg("hostname")) ? strcpy(conman.cfg.wifihost, server.arg("hostname").c_str() ) : "";
      (server.hasArg("esptitle")) ? strcpy(conman.cfg.esptitle, server.arg("esptitle").c_str() ) : "";
      conman.saveConfig();
      Serial.println("Konfiguration im EEPROM gespeichert.");
    } 

    // Konfiguration wird hier gelöscht.
    if(server.hasArg("del_eeprom")) {
      conman.deleteConfig();
      Serial.println("Konfiguration wurde gelöscht.");
    }
    
    Serial.println("Startup");
    String output = XMLBEGIN "<settings>";
    output += "<wid>" + String(conman.cfg.wifissid) + "</wid>";
    output += "<wuser>" + String(conman.cfg.wifiuser) + "</wuser>";
    output += "<wpw>" + String(conman.cfg.wifipass) + "</wpw>";
    output += "<hostname>" + String(conman.cfg.wifihost) + "</hostname>";
    output += "<esptitle>" + String(conman.cfg.esptitle) + "</esptitle>";
    output += "</settings>" XMLEND;
    
    server.send(200, "text/xml", output);
  });

  server.on("/temperatur/", []() {
    Serial.println("Temperatur XML");
    String output = XMLBEGIN "<temperatur>";
    output += "<aussentemperatur>" + sensoren.getDS18B20Celsius(0) + "</aussentemperatur>";
    output += "<innentemperatur>" + sensoren.getDS18B20Celsius(1) + "</innentemperatur>";
    output += "</temperatur>" XMLEND;
    server.send(200, "text/xml", output);
  });
  
  server.on("/vibrator/", []() {
    
    programm.prange = (server.hasArg("range")) ? server.arg("range") : programm.prange;
    programm.pdrehzahl = programm.prange.toInt() * 10;
    
    programm.prms = (server.hasArg("rms")) ? server.arg("rms") : programm.prms;
    programm.pdelayms = programm.prms.toInt() * 300;
    
    String output = XMLBEGIN "<vibrator><range>" + programm.prange + "</range><rms>" + programm.prms + "</rms></vibrator>" XMLEND;
    server.send(200, "text/xml", output);
    yield();
  });

  server.onNotFound([]() {
    server.send(404, "text/html", "404: Not Found");
  });

  server.begin();
  Serial.println("HTTP server started");
  yield();
  Serial.println(programm.pdrehzahl);
  Serial.println(programm.pconfigmanager->cfg.esptitle);
  Serial.println(programm.pds18b20->getDS18B20Celsius(0));
}

void loop() {
  // Der Server arbeitet hier.
  server.handleClient();
  // Kleine Pause zum Erhalt der WiFi-Verbindung.
  yield();
  // Hier dreht der Motor
  (programm.pdrehzahl > 200) ? analogWrite(MOTOR, programm.pdrehzahl) : analogWrite(MOTOR, 0);
  // Kleine Pause zum Erhalt der WiFi-Verbindung.
  yield();
}

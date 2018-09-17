/**
   Sketch für ESP Webserver

   @author Stefan Krone
   @version 0.0.0
*/

#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ConfigManager.h"
#include "DS18B20.h"

#define XMLBEGIN "<?xml version=\"1.0\" encoding=\"UTF-8\"?><?xml-stylesheet type=\"text/xsl\" href=\"/design.xsl\"?><root><head><title>ESP8266 - Websever</title><esptitle>Steckdose :: Küche</esptitle></head>"
#define XMLEND "</root>"
#define MOTOR 4

using namespace std;

#define ONE_WIRE_BUS 5

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature templib(&oneWire);

DS18B20 sensoren(ONE_WIRE_BUS);

ESP8266WebServer server(80);

int drehzahl = 0;
int delayms = 0;
String range = "0";
String rms = "0";

ConfigManager conman;

/**
   Das WiFi wird hier gestartet, die Zugangsdaten werden aus dem EEPROM speicher geholt.
   Wenn keine Zugangsdaten im Speicher hinterlegt worden sind oder kein keine Verbindung zu einem WLAN möglich ist,
   wird ein Accesspoint geöffnet. Nach 20 Versuchen wird ein AccessPoint geöffnet, die Zeit eines Versuches beträgt 500ms.

   @return Normalmode - true, AcceesPointMode - false
*/
void startWiFi() {
  // Wenn aus dem Speicher die Zugangsdatengeholt werden konnten verbindet sich der ESP mit dem WLAN. Wenn nicht wird ein Accesspoint geöffnet.
  if (!startWiFiSTA()) {
    startWiFiAT(false);
  }
}


bool startWiFiSTA() {
  WiFi.persistent(false);
  WiFi.mode(WIFI_OFF);
  WiFi.mode(WIFI_STA);
  WiFi.hostname(conman.cfg.wifihost);
  MDNS.begin(conman.cfg.wifihost);
  delay(200);
  WiFi.begin(conman.cfg.wifissid, conman.cfg.wifipass);

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    delay(100);
    Serial.print(i);
    if (i > 50) {
      Serial.println("Die Verbindung mit dem WLAN konnte nicht aufgebaut werden. Es wird ein Accesspoint gestartet.");
      return false;
    }
    i++;
  }

  Serial.println("");
  Serial.println(WiFi.localIP());
  return true;
}

/**
   Accespointmodus
   Hostname: http://192.168.0.1/
*/
bool startWiFiAT(bool openAP) {
  IPAddress local_IP(192, 168, 0, 1);
  IPAddress gateway(192, 168, 4, 9);
  IPAddress subnet(255, 255, 255, 0);

  WiFi.mode(WIFI_OFF);
  WiFi.mode(WIFI_AP);
  WiFi.hostname(conman.cfg.wifihost);

  WiFi.softAPConfig(local_IP, gateway, subnet);
  (openAP) ? WiFi.softAP(conman.cfg.wifihost) : WiFi.softAP(conman.cfg.wifihost, conman.cfg.wifihost);

  Serial.print("IP-Adresse: ");
  Serial.println(WiFi.softAPIP());
  Serial.printf("MAC address = %s\n", WiFi.softAPmacAddress().c_str());
  return true;
}

/**
   Programm startet hier.
*/
void setup() {
 
  Serial.begin(115200);
  delay(200);
  Serial.setDebugOutput(true);
  
  Serial.println( (!SPIFFS.begin()) ? "SPIFFS Mount failed" : "SPIFFS Mount succesfull");
  Serial.println("Webserver wird gestartet!");

  // Die Konfiguration lade ich hier.
  conman.loadConfig();
  templib.begin();
  
  Serial.printf("Die Länge des Strings beträgt: %i\n", sizeof(conman.cfg.wifiuser) / sizeof(*conman.cfg.wifiuser) ); 
  /*std::string hallo = conman.cfg.wifiuser;
  Serial.println( (hallo.empty()) ? "Ja" : "Nein" ); */
  startWiFi();
  
  //delay(200);
  Serial.printf("Temperatur der Klasse DS18B20 beträgt %s.\n", sensoren.getDS18B20Celsius(0));
  
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
    output += "<aussentemperatur>" + String(getTemperature(0)) + "</aussentemperatur>";
    output += "<innentemperatur>" + String(getTemperature(1)) + "</innentemperatur>";
    output += "</temperatur>" XMLEND;
    server.send(200, "text/xml", output);
  });
  
  server.on("/vibrator/", []() {
    
    range = (server.hasArg("range")) ? server.arg("range") : range;
    drehzahl = range.toInt() * 10;
    
    rms = (server.hasArg("rms")) ? server.arg("rms") : rms;
    delayms = rms.toInt() * 300;
    
    String output = XMLBEGIN "<vibrator><range>" + range + "</range><rms>" + rms + "</rms></vibrator>" XMLEND;
    server.send(200, "text/xml", output);
    yield();
  });

  server.onNotFound([]() {
    server.send(404, "text/html", "404: Not Found");
  });

  server.begin();
  Serial.println("HTTP server started");
  yield();
}

void loop() {
  server.handleClient();
  yield();
  // Hier dreht der Motor
  (drehzahl > 200) ? analogWrite(MOTOR, drehzahl) : analogWrite(MOTOR, 0);
  // Kleine Pause zum Erhalt der WiFi-Verbindung.
  yield();
}

char* getTemperature(int sensor) {
  
  int dscounter = templib.getDS18Count();
  
  if(dscounter > 0 && sensor < dscounter){
    
    yield();
    templib.requestTemperatures();
    float tempC = templib.getTempCByIndex(sensor);
    yield();
    
    if(tempC > -127){
      char* test = "Test";
      dtostrf(tempC, 2, 1, test);
      return test;
    }
    
  } 
  return "Error";
}

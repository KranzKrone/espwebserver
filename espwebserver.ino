/**
   Sketch für ESP Webserver

   @author Stefan Krone
   @version 1.0.0
*/

#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>
#include <FS.h>
#include <stdio.h>
#include <stdlib.h>
#include "DS18B20.h"

#define TEST_MODUS true

#define HOSTNAME "temperatur"
#define WIFI_SSID "Internet"
#define WIFI_PWORD "DownTownFMP!"

#define XMLBEGIN "<?xml version=\"1.0\" encoding=\"UTF-8\"?><?xml-stylesheet type=\"text/xsl\" href=\"/design.xsl\"?><root><head><title>ESP8266 - Websever</title></head>"
#define XMLEND "</root>"
#define MOTOR 4


#define ONE_WIRE_BUS 5

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature templib(&oneWire);

DS18B20 sensoren(ONE_WIRE_BUS);

ESP8266WebServer server(80);

int drehzahl = 0;
int delayms = 0;
String range = "0";
String rms = "0";


/**
   Das WiFi wird hier gestartet, die Zugangsdaten werden aus dem EEPROM speicher geholt.
   Wenn keine Zugangsdaten im Speicher hinterlegt worden sind oder kein keine Verbindung zu einem WLAN möglich ist,
   wird ein Accesspoint geöffnet. Nach 20 Versuchen wird ein AccessPoint geöffnet, die Zeit eines Versuches beträgt 500ms.

   @return Normalmode - true, AcceesPointMode - false
*/
void startWiFi() {

  // Wenn aus dem Speicher die Zugangsdatengeholt werden konnten verbindet sich der ESP mit dem WLAN. Wenn nicht wird ein Accesspoint geöffnet.

  if (TEST_MODUS) {
    bool startUp = startWiFiSTA();
    if (!startUp) {
      startWiFiAT(false);
    }
  } else {
    startWiFiAT(false);
  }
}


bool startWiFiSTA() {
  WiFi.persistent(false);
  WiFi.mode(WIFI_OFF);
  WiFi.mode(WIFI_STA);
  WiFi.hostname(HOSTNAME);
  MDNS.begin(HOSTNAME);
  delay(200);
  WiFi.begin(WIFI_SSID, WIFI_PWORD);

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
  WiFi.hostname(HOSTNAME);

  WiFi.softAPConfig(local_IP, gateway, subnet);
  if (openAP)
    WiFi.softAP(HOSTNAME);
  else
    WiFi.softAP(HOSTNAME, HOSTNAME);

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
  
  if (!SPIFFS.begin()){
    Serial.println("SPIFFS Mount failed");
  } else {
    Serial.println("SPIFFS Mount succesfull");
  }
  
  Serial.println("Webserver wird gestartet!");
  
  EEPROM.begin(512);
  templib.begin();

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
    Serial.println("Startup");

    String output = XMLBEGIN "<settings>";
    output += (server.hasArg("wid")) ? "<wid>" + server.arg("wid") + "</wid>":"";
    output += (server.hasArg("wpw")) ? "<wpw>" + server.arg("wpw") + "</wpw>":"";
    output += (server.hasArg("hostname")) ? "<hostname>" + server.arg("hostname") + "</hostname>" : "";
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
    delay(10);
  });

  server.onNotFound([]() {
    server.send(404, "text/html", "404: Not Found");
  });

  server.begin();
  delay(20);
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
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

/**
   Sketch für ESP Webserver

   @author Stefan Krone
   @version 1.0.0
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <EEPROM.h>
#include <FS.h>
#include <stdio.h>
#include <stdlib.h>


#define HEADER = "<head><title>ESP Webserver</title></head>"

#define TEST_MODUS true

#define HOSTNAME "esp8266"
#define WIFI_SSID "Internet"
#define WIFI_PWORD "DownTownFMP!"

#define XMLBEGIN "<?xml version=\"1.0\" encoding=\"UTF-8\"?><?xml-stylesheet type=\"text/xsl\" href=\"/design.xsl\"?><root>"
#define XMLEND "</root>"
#define MOTOR 4

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
    delay(500);
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

  startWiFi();
  
  // Statische Dateien wie CSS, JS wird geladen.
  server.serveStatic("/materialize.min.css", SPIFFS, "/materialize.min.css", "max-age=3600");
  server.serveStatic("/materialize.min.js", SPIFFS, "/materialize.min.js", "max-age=3600");
  server.serveStatic("/design.xsl", SPIFFS, "/design.xsl", "max-age=60");

  // Hier werden die Seiten im Server definiert.
  server.on("/eeprom/", []() {
    Serial.println("Startup");
    // read eeprom for ssid and pass
    Serial.println("Reading EEPROM ssid");
    String esid;
    for (int i = 0; i < 32; ++i)
    {
      esid += char(EEPROM.read(i));
    }
    Serial.print("SSID: ");
    Serial.println(esid);
    Serial.println("Reading EEPROM pass");
    String epass = "";
    for (int i = 32; i < 96; ++i)
    {
      epass += char(EEPROM.read(i));
    }
    Serial.print("PASS: ");
    Serial.println(epass);
    server.send(200, "text/html", "Mini Webserver Beispiel<br />SSID: " + esid + " | PWD: " + epass);
  });
  
  
  // Hier werden die Seiten im Server definiert.
  server.on("/", []() {
    Serial.println("Startup");

    String output = XMLBEGIN "<settings>";
    
    if(server.hasArg("wid")){
       Serial.println(server.arg("wid"));
       output += "<wid>" + server.arg("wid") + "</wid>";
    }
    if(server.hasArg("wpw")){
       output += "<wpw>" + server.arg("wpw") + "</wpw>";
    }
    if(server.hasArg("hostname")){
       output += "<hostname>" + server.arg("hostname") + "</hostname>";
    }
    output += "</settings>" XMLEND;
    Serial.println(output);
    server.send(200, "text/xml", output);
  });

  server.on("/temperatur/", []() {
    Serial.println("Startup");

    String output = XMLBEGIN "<temperatur>";
    
    output += "</temperatur>" XMLEND;
    Serial.println(output);
    server.send(200, "text/xml", output);
  });

  server.begin();
  Serial.println("HTTP server started");

  server.on("/vibrator/", []() {
    
    if(server.hasArg("range")){
      range = server.arg("range");
    }
    drehzahl = range.toInt() * 10;
    
    if(server.hasArg("rms")){
      rms = server.arg("rms");
    }
    
    delayms = rms.toInt() * 300;
    
    String output = XMLBEGIN "<vibrator><range>" + range + "</range><rms>" + rms + "</rms></vibrator>" XMLEND;
    Serial.println(output);
    server.send(200, "text/xml", output);
  });

  server.on("/settings/", []() {
    String ssid = server.arg("ssid");
    String pwd = server.arg("pwd");

    int lssid = ssid.length();
    int lpwd = pwd.length();

    String errortext = (lssid == 0) ? "Bitte geben Sie SSID und Passwort ein." : "";

    if (lssid > 0) {
      Serial.println("writing eeprom ssid:");
      for (int i = 0; i < ssid.length(); ++i)
      {
        EEPROM.write(i, ssid[i]);
        Serial.print("Wrote: ");
        Serial.println(ssid[i]);
      }

      Serial.println("writing eeprom pass:");
      for (int i = 0; i < pwd.length(); ++i)
      {
        EEPROM.write(32 + i, pwd[i]);
        Serial.print("Wrote: ");
        Serial.println(pwd[i]);
      }
      
      delay(300);
      EEPROM.commit();
    }


    server.send(200, "text/html", errortext + "<h1>WLAN-Einstellungen</h1><form><input type=\"text\" name=\"ssid\" /><input type=\"text\" name=\"pwd\" /><input type=\"submit\" value=\"Speichern\" /></form>");
  });

  server.onNotFound([]() {
    server.send(404, "text/html", "404: Not Found");
  });

  server.begin();
}

void loop() {
  server.handleClient();

  if (drehzahl > 200) {
    analogWrite(MOTOR, drehzahl);
  } else {
    analogWrite(MOTOR, 0);
  }
}

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

#define HEADER = "<head><title>ESP Webserver</title></head>"

#define TEST_MODUS true

#define HOSTNAME "esp8266"
#define WIFI_SSID ""
#define WIFI_PWORD ""

ESP8266WebServer server(80);

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

  Serial.begin(9600);
  delay(200);
  Serial.println("Webserver wird gestartet!");

  startWiFi();

  // Hier werden die Seiten im Server definiert.
  server.on("/", []() {
    server.send(200, "text/html", "Mini Webserver Beispiel<br /><input type=\"range\" name=\"range\" />");
  });

  server.on("/settings/", []() {
    String range = server.arg("range");
    Serial.print("Range  ist ");
    Serial.println(range);
    server.send(200, "text/html", "<h1>Einstellungen</h1><form><input type=\"range\" name=\"range\" value=" + range + " /><input type=\"submit\" value=\"Speichern\" /></form>");
  });

  server.on("/settings/", []() {
    server.send(200, "text/html", "<h1>Einstellungen</h1><form post=\"handleGenericArgs\"><input type=\"range\" name=\"range\" /><input type=\"submit\" value=\"Speichern\" /></form>");
  });

  server.onNotFound([]() {
    server.send(404, "text/html", "404: Not Found");
  });

  server.begin();
}

void loop() {
  server.handleClient();
}

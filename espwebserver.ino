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
    startWiFiSTA();
  } else {
    startWiFiAT();
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

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(WiFi.localIP());
  return true;
}

/**
   Accespointmodus
   Hostname: http://192.168.0.1/
*/
bool startWiFiAT() {
  IPAddress local_IP(192, 168, 0, 1);
  IPAddress gateway(192, 168, 4, 9);
  IPAddress subnet(255, 255, 255, 0);

  WiFi.mode(WIFI_OFF);
  WiFi.mode(WIFI_AP);
  WiFi.hostname(HOSTNAME);

  WiFi.softAPConfig(local_IP, gateway, subnet);
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

  // Hier werden die Seiten im Server definiert.
  server.on("/", []() {
    server.send(200, "text/html", "Mini Webserver Beispiel");
  });

  server.onNotFound([]() {
    server.send(404, "text/html", "404: Not Found");
  });

  server.begin();
}

void loop() {
  server.handleClient();
}

#include "WiFiManager.h"
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WString.h>
#include <vector>

int reconnectcounter = 0;
String _lokalip = "";

WiFiManager::WiFiManager(){};

bool WiFiManager::begin(String wifissid, String wifipass, String wifihost, String apname, String appass){
  
  bool _wifi = WiFiManager::connectWiFi(wifissid, wifipass, wifihost);
  
  if(_wifi){
    Serial.println(WiFi.localIP());
    Serial.printf("Verbindung zu Netzwerk %s hergstellt.", wifissid.c_str());
    return true;
  } else {
    bool _wifiap = WiFiManager::createWiFiAP(apname, appass);
    Serial.printf("Accespoint gestartet - %s.\n", ((_wifiap) ? "Ja" : "Nein"));
    return true;
  }
  return false;
}

/**
   Accespointmodus
   Hostname: http://192.168.0.1/
*/
bool WiFiManager::createWiFiAP(String ap_name, String ap_pass) {
  IPAddress local_IP(192, 168, 0, 1);
  IPAddress gateway(192, 168, 4, 9);
  IPAddress subnet(255, 255, 255, 0);

  WiFi.mode(WIFI_OFF);
  WiFi.mode(WIFI_AP);
  WiFi.persistent(false);

  WiFi.softAPConfig(local_IP, gateway, subnet);
  (ap_pass.length() == 0) ? WiFi.softAP(ap_name.c_str()) : WiFi.softAP(ap_name.c_str(), ap_pass.c_str());

  Serial.print("IP-Adresse: ");
  Serial.println(WiFi.softAPIP());
  Serial.printf("MAC address = %s\n", WiFi.softAPmacAddress().c_str());
  return true;
}

/**
 * Eine Verbindung zu einem WiFi Netzwerk wird hergestellt.
 */
bool WiFiManager::connectWiFi(String wifissid, String wifipass, String wifihost){
  WiFi.mode(WIFI_OFF);
  WiFi.mode(WIFI_STA);
  WiFi.hostname(wifihost.c_str());
  MDNS.begin(wifihost.c_str());
  delay(200);
  (wifipass.length() == 0) ? WiFi.begin(wifissid.c_str()) : WiFi.begin(wifissid.c_str(), wifipass.c_str());

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    delay(100);
    if (i > 50) {
      Serial.printf("Verbindung zu WiFi mit der SSID - %s (%s) - konnte nicht hergestellt werden.\n", wifissid.c_str(), wifipass.c_str());
      return false;
    }
    i++;
  }
  _lokalip = WiFi.localIP().toString();
  return true;
   
}

std::vector<WiFiManager::WiFiData> WiFiManager::lookUpWiFi(){
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  std::vector<WiFiManager::WiFiData> wlanlist;
  
  int _scannet = WiFi.scanNetworks();
  for (int i = 0; i < _scannet; ++i){
    WiFiData wdata;
    strcpy(wdata.wifissid, WiFi.SSID(i).c_str());
    wlanlist.push_back(wdata);
  }
  yield();

  return wlanlist;
}

#include "WiFiManager.h"
#include <ESP8266WiFi.h>
#include <string>

WiFiManager::WiFiManager(){};

std::string[] WiFiManager::lookUpWiFi(){
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  int wifiids = WiFi.scanNetworks();
  std::string outprint[wifiids];
  
  for (int i = 0; i < wifiids; ++i){
    byte encryption = WiFi.encryptionType(i);
    String oprint = String(i) + " " + WiFi.SSID(i) + " " + WiFi.RSSI(i);
    oprint += " Encryption Type: " + String(encryption,HEX);
    oprint += (encryption == ENC_TYPE_NONE) ? " " : "*";
    strcpy(outprint[wifiids], oprint.c_str());
  }

  return outprint;
}

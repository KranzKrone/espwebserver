#ifndef WifiManager_h
#define WifiManager_h

#include <WString.h>
#include <vector>

class WiFiManager
{
  public:
  
    struct WiFiData {
      char wifissid[64];
      char wifiissd[64];
    };
    
    int reconnectcounter;
    String _lokalip;
    
    WiFiManager();
    bool begin(String wifissid, String wifipass, String wifihost, String apname, String appass);
    bool connectWiFi(String wifissid, String wifipass, String wifihost);
    bool createWiFiAP(String ap_name, String ap_pass);
    std::vector<WiFiManager::WiFiData> lookUpWiFi();
};

#endif

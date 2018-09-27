// #include <stdlib.h>
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
    void getCurrentWiFi();
    bool connectWiFi(String wifissid, String wifipass, String wifihost);
    bool createWiFiAP(String ap_name, String ap_pass);
    void reconnectWiFi();
    std::vector<WiFiManager::WiFiData> lookUpWiFi();
};

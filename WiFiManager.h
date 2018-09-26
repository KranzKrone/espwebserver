#include <string>

class WiFiManager
{
  public:
  	WiFiManager();
  	void getCurrentWiFi();
  	bool connectWiFi();
  	bool createWiFiAP();
  	void reconnectWiFi();
    std::string[] lookUpWiFi();
};

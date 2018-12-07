#include "WebHook.h"
#include <Arduino.h>
#include <ESP8266HTTPClient.h>

/**
 * ´Call a HTTP Webhook 
 * 
 * see https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/client-secure-examples.html
 * and 
 */
int WebHook::httpsGetAsyc(String _url, String _publicKey){
  
  HTTPClient http;

  if(_url.length() != 0 && _url.startsWith("http")) { 
    (_publicKey.length() == 0) ? http.begin(_url) : http.begin(_url, _publicKey);
    int httpCode = http.GET();
    // Testout Output
    // Serial.println(http.getString());
    http.end();
    return httpCode;
  } else {
    return -99;
  }
}

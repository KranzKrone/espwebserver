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

  if(_publicKey == "") { 
    return -99;
  } else {
    http.begin(_url, _publicKey);
    int httpCode = http.GET();
    Serial.printf("HTTPS Status %d\n", httpCode);
    // Testout Output
    // Serial.println(http.getString());
    http.end();
    return httpCode;
  }
}

#include "WebHook.h"
#include <Arduino.h>
#include <ESP8266HTTPClient.h>


WebHook::WebHook(Programm*_programm){
  programm = _programm;
}

/**
 * Hier werden Informationen an einen bestehenden Webhook gesendet. 
 * Hierzu muss der Fingerprint und die Url bekannt sein, die Daten werden aus dem Configuarationsobjekt heraus. 
 * 
 * TODO: Hier muss noch weiterprogrammiert werden.
 */
int sendUrlQuery(String _urlQuery){
  /*
  HTTPClient http;
  (_publicKey != "") ? http.begin(_url, _publicKey) : http.begin(_url);
  int httpCode = http.GET();
  Serial.printf("HTTPS Status %d\n", httpCode);
  http.end();*/
  return -1;
}

/**
 * ´Call a HTTP Webhook 
 * 
 * see https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/client-secure-examples.html
 * and 
 */
int WebHook::httpsGetAsyc(String _url, String _publicKey){
  
  HTTPClient http;
  (_publicKey != "") ? http.begin(_url, _publicKey) : http.begin(_url);
  int httpCode = http.GET();
  Serial.printf("HTTPS Status %d\n", httpCode);
  http.end();
  return httpCode;
}

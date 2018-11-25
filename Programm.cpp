#include "Programm.h"
#include "Arduino.h"
#include "WebHook.h"

Programm::Programm(ConfigManager*_cm, DS18B20*_ds18b20){
  pconfigmanager = _cm;
  pds18b20 = _ds18b20;
}

void Programm::startup(){
  // Hier setze ich die Startbedingungen für meine Steckdose
  Serial.println("Pins wurden gesetzt");
  pinMode(P13LED, OUTPUT);
  digitalWrite(P13LED, ponoff);
  pinMode(P12RELAY, OUTPUT);
  digitalWrite(P12RELAY, ponoff);
}

void Programm::s20_switch(){
  Serial.printf("Steckdose wurde %sgeschaltet.\n", (ponoff) ? "aus" : "ein");
  if(ponoff){
    ponoff = false;
    digitalWrite(P13LED, ponoff);
    digitalWrite(P12RELAY, ponoff);
  } else {
    ponoff = true;
    digitalWrite(P13LED, ponoff);
    digitalWrite(P12RELAY, ponoff);
  }
}

void Programm::sendTempData(){
    long _zeit = millis();
    int _time = (int) _zeit % 300000; // Sollten fünf Minuten sein. 300000 für 5 Minuten.
    if( _time <= 1){
      Serial.printf("Nächsten fünf Minuten - %d\n", _time);
      String _tempOut = pds18b20->getDS18B20Celsius(0);
      String _send = "https://userpage.fu-berlin.de/truppels/input.php?temp=" + _tempOut;
      WebHook::httpsGetAsyc(_send, "415f636b60a226c1db91d7ba7cc94b30c1868557");
    }
}

#include "Programm.h"
#include <WString.h>

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

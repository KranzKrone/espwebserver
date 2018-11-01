#include "DS18B20.h"
#include <OneWire.h>
#include <DallasTemperature.h>

DallasTemperature templib;

DS18B20::DS18B20(OneWire* ow){
  templib.setOneWire(ow);
  templib.begin(); 
}

String DS18B20::getDS18B20Celsius(int sensor){
  
  int dscounter = templib.getDS18Count();
  Serial.printf("Temperatursensoranzahl: %d Stück.\n", dscounter);
  
  if(dscounter > 0 && sensor < dscounter){
    
    yield();
    templib.requestTemperatures();
    float tempC = templib.getTempCByIndex(sensor);
    yield();
    
    if(tempC > -127){
      return dtostrf(tempC, 2, 1, (char*)"Test");
    }
    
  } 
  return "Error";
}

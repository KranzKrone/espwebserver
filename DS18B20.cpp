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
  
  if(dscounter > 0 && sensor < dscounter){
    
    yield();
    templib.requestTemperatures();
    float tempC = templib.getTempCByIndex(sensor);
    yield();
    
    if(tempC > -127){
      char* test = "Test";
      dtostrf(tempC, 2, 1, test);
      return test;
    }
    
  } 
  return "Error";
}

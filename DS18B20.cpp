#include "DS18B20.h"
#include <OneWire.h>
#include <DallasTemperature.h>

DS18B20::DS18B20(int owp)
: onewireport(owp)
{
}

char* DS18B20::getDS18B20Celsius(int sensor){
  return "Error";
}

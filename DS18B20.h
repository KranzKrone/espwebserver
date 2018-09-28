#include <OneWire.h>
#include <DallasTemperature.h>
#include <WString.h>

class DS18B20
{
  public:
    int onewireport;
    DallasTemperature templib;
    
    DS18B20(OneWire* ow);
    String getDS18B20Celsius(int sensor=0);
};

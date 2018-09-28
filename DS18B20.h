
class DS18B20
{
  public:
    int onewireport;
    DS18B20(int onewire=5);
    char* getDS18B20Celsius(int sensor=0);
};

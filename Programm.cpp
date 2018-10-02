#include "Programm.h"
#include <WString.h>

Programm::Programm(ConfigManager*_cm, DS18B20*_ds18b20){
  pconfigmanager = _cm;
  pds18b20 = _ds18b20;
}

/**
 * Sketch for ESP Webserver, usefull for different projects.
 * 
 * @author Stefan Krone
 * @version 0.0.0
 */

#include <OneWire.h>
#include "ConfigManager.h"
#include "WiFiManager.h"
#include "DS18B20.h"
#include "ServerManager.h"
#include "Programm.h"

#define MOTOR 4

#define ONE_WIRE_BUS 5

// Objects for the programm
ConfigManager conman;
WiFiManager wman;
OneWire oneWire(ONE_WIRE_BUS);
DS18B20 sensoren(&oneWire);

// Im Programm speichere ich die Veriablen für die Bewegungen und andere Dinge
Programm programm(&conman, &sensoren);
ServerManager servers(&programm);

/**
 * DE: Initialisierung des Programms
 * EN: Programm is init here
 */
void setup() {
 
  Serial.begin(115200);
  delay(200);
  Serial.setDebugOutput(false);

  // Die Konfiguration lade ich hier.
  conman.loadConfig();
  // Hier wird WLan gestartet.
  wman.begin(conman.cfg.wifissid, conman.cfg.wifipass, conman.cfg.wifihost, "ESPDEV", "");

  Serial.println("HTTP server started");
  programm.startup();
  yield();
}

void loop() {
  // serverloop is there
  servers.serverLoop();
  // Kleine Pause zum Erhalt der WiFi-Verbindung.
  yield();
  // Hier dreht der Motor
  (programm.pdrehzahl > 200) ? analogWrite(MOTOR, programm.pdrehzahl) : analogWrite(MOTOR, 0);
  // Kleine Pause zum Erhalt der WiFi-Verbindung.
  yield();
}

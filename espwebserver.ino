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

#define DEBUG false

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
  Serial.setDebugOutput(DEBUG);
  Serial.print("Programm wird gestartet - ");
  Serial.println(programm.state);

  // Die Konfiguration lade ich hier.
  conman.loadConfig();
  // if conman empty load data, better for work with them.
  Serial.printf("Speicher ? - %s\n", (conman.firstData()) ? "Speicher wurde neu gesetzt.":"OK."); 
  
  // Hier wird WLan gestartet.
  wman.begin(conman.cfg.wifissid, conman.cfg.wifipass, conman.cfg.wifihost, "ESPDEV", "");

  Serial.println("HTTP server started");
  programm.startup();
  // Ich setze im Programm, dass ich im Accesspoint Modus gestartet bin.
  if(wman.wState == wman.wifiState::ACCESSPOINT){
    programm.state = programm.appState::RUNNING_AP;
  }
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
  // Aufruf zum senden an einen WebHook
  programm.sendTempData();
  yield();
}

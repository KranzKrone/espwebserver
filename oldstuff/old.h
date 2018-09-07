  server.on("/oldsettings/", []() {
    String ssid = server.arg("ssid");
    String pwd = server.arg("pwd");

    int lssid = ssid.length();
    int lpwd = pwd.length();

    String errortext = (lssid == 0) ? "Bitte geben Sie SSID und Passwort ein." : "";

    if (lssid > 0) {
      Serial.println("writing eeprom ssid:");
      for (int i = 0; i < ssid.length(); ++i)
      {
        EEPROM.write(i, ssid[i]);
        Serial.print("Wrote: ");
        Serial.println(ssid[i]);
      }

      Serial.println("writing eeprom pass:");
      for (int i = 0; i < pwd.length(); ++i)
      {
        EEPROM.write(32 + i, pwd[i]);
        Serial.print("Wrote: ");
        Serial.println(pwd[i]);
      }
      
      delay(300);
      EEPROM.commit();
    }


    server.send(200, "text/html", errortext + "<h1>WLAN-Einstellungen</h1><form><input type=\"text\" name=\"ssid\" /><input type=\"text\" name=\"pwd\" /><input type=\"submit\" value=\"Speichern\" /></form>");
  });

// Hier werden die Seiten im Server definiert.
  server.on("/eeprom/", []() {
    Serial.println("Startup");
    // read eeprom for ssid and pass
    Serial.println("Reading EEPROM ssid");
    String esid;
    for (int i = 0; i < 32; ++i)
    {
      esid += char(EEPROM.read(i));
    }
    Serial.print("SSID: ");
    Serial.println(esid);
    Serial.println("Reading EEPROM pass");
    String epass = "";
    for (int i = 32; i < 96; ++i)
    {
      epass += char(EEPROM.read(i));
    }
    Serial.print("PASS: ");
    Serial.println(epass);
    server.send(200, "text/html", "Mini Webserver Beispiel<br />SSID: " + esid + " | PWD: " + epass);
  });  
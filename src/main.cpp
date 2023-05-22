#include "Communication/websocket.h"
// #include "Command/storage.h"
#include <EEPROM.h>
#include <Arduino.h>
#include <WiFi.h>

#define EEPROM_SIZE 2500

const char *ssid = "Step";
const char *password = "@2805_1984@";
const char *URL = "wss://localhost:7193/ws";
int address = 0;
void setup()
{
  Serial.begin(115200);
  Serial.println("Initialize System");
}

int address1 = 0;
void loop()
{

  // Write data into eeprom
  // Read data from eeprom


  /*float readParam;
    EEPROM.get(address, readParam); //readParam=EEPROM.readFloat(address);
    Serial.print("Read param = ");
    Serial.println(readParam);*/

  delay(1000);
}

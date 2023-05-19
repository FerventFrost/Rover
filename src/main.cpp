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

  EEPROM.begin(EEPROM_SIZE);

  StructBody plan[3] = {
      {1, 0, 0, 50, 3, 15},
      {2, 1, 2, 30, 2, 16},
      {3, 0, 0, 25, 3, 17}};
  address = 0;
  for (int i = 0; i < 3; i++)
  {
    EEPROM.put(address, plan[i]); // EEPROM.put(address, boardId);
    address += sizeof(plan[i]);
    EEPROM.commit();
  }
}

int address1 = 0;
void loop()
{

  // Write data into eeprom
  // Read data from eeprom

  StructBody readId;
  EEPROM.get(address1, readId); // EEPROM.get(address,readId);

  Serial.print("Read ID = ");
  Serial.println(readId.PlanID);
  Serial.println(readId.SequenceID);
  Serial.println(readId.SubSystemID);
  Serial.println(readId.CommandID);
  Serial.println(readId.Delay);
  Serial.println(readId.CommandRepeat);

  address1 += sizeof(readId); // update address value

  /*float readParam;
    EEPROM.get(address, readParam); //readParam=EEPROM.readFloat(address);
    Serial.print("Read param = ");
    Serial.println(readParam);*/

  delay(1000);
}

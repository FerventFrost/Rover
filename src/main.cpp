// #include "Communication/websocket.h"
#include "Command/Rover.h"
// #include "Command/CameraUART.h"
// #include "Command/ESPFlash.h"
// #include "StateController.h"
// #include <EEPROM.h>
#include <Arduino.h>
// #include <WiFi.h>

#define EEPROM_SIZE 2500

// const char *ssid = "Step";
// const char *password = "@2805_1984@";
// const char *URL = "wss://localhost:7193/ws";
// FilePath filePath;

  static const char trigPin = 9;
  static const char echoPin = 10;
void setup()
{
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
  // RoverMovement::SetSpeed(120);
  // RoverMovement::SetupUltraSonic();
  // Serial1.begin(BAUD_RATE, SERIAL_8N1, RXD_PIN, TXD_PIN);
  // Serial.println("Initialize System");
  // ESPFlash::SetupFlash();
  // CameraUART::SetupUART();
  // StructBody Command;
  // Command.PlanID = 25005;
  // Command.SequenceID = 3;
  // Command.CommandID = 12;
  // Command.SubSystemID = 2;
  // Command.Delay = 0;
  // Command.CommandRepeat = 1;

  // ESPFlash::WriteCommand(Command);
  // Command.PlanID = 35005;
  // ESPFlash::WriteCommand(Command);

  // StructBody Command2 = ESPFlash::RetriveCommands();
  // Serial.println(Command2.PlanID);
  // Serial.println(Command2.SequenceID);
  // Serial.println(Command2.CommandID);
  // Serial.println(Command2.SubSystemID);
  // Serial.println(Command2.Delay);
  // Serial.println(Command2.CommandRepeat);
  // Command2 = ESPFlash::RetriveCommands();
  // Serial.println(Command2.PlanID);
  // Serial.println(Command2.SequenceID);
  // Serial.println(Command2.CommandID);
  // Serial.println(Command2.SubSystemID);
  // Serial.println(Command2.Delay);
  // Serial.println(Command2.CommandRepeat);
}

void loop()
{
  // Serial.println(RoverMovement::ReadUltraSonic());
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  // Calculating the distance
  short int Distance = pulseIn(echoPin, HIGH) * 0.034 / 2;
  Serial.println(Distance);
  delay(1000);
  // StructBodyImage *Image = new StructBodyImage();
  // Image->PlanID= 25005;
  // Image->SequenceID = 3;
  // Image->OperationType = 1;
  // CameraUART::SendUARTData(Image);
  // delete Image;
  // // Serial1.println("Sending Image");
  // delay(1000);

  // Write data into eeprom
  // Read data from eeprom

  /*float readParam;
    EEPROM.get(address, readParam); //readParam=EEPROM.readFloat(address);
    Serial.print("Read param = ");
    Serial.println(readParam);*/
  delay(500);
}

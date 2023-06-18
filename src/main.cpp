#include <Arduino.h>
#include "Communication\WebSocket.h"
#include "StateController.h"
#include "WiFi.h"
#include "Command\Rover.h"
#include "Command\Queue.h"

// const char *ssid = "Shamsia";
// const char *password = "Shamsia#202030";
// const char *URL = "ws://192.168.1.20:6969/api/FrontSockets/RoverData";
// const char *ssid = "Shamsia2";
// const char *password = "shamsiaspace#230523";
const char *ssid = "Voda";
const char *password = "12312356";
const char *URL = "ws://192.168.1.2:9090/api/FrontSockets/RoverData";
WebSocket *_socketHandler;
ByteQueue *DataQueue;
StateController *state;
void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  DataQueue = new ByteQueue();
  Serial.println("Connected");
  _socketHandler = new WebSocket(URL, DataQueue);
  state = new StateController(_socketHandler, DataQueue);
  Serial.println("Established");
  Sensors::SetupDHT();
  Sensors::SetupMPU();
  Sensors::SetupUltrasonic();
  // RoverMovement::SetSpeed(150);
  delay(2000);
}

void loop()
{
  state->OnlineState();
  delay(1000);
}

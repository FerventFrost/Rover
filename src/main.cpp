#include <Arduino.h>
#include "Communication\WebSocket.h"
#include "WiFi.h"
#include "Command\Rover.h"
#include "Command\Sensors.h"
#include "Command\Queue.h"
// #define IN1 2
// #define IN2 4
// #define IN3 15
// #define IN4 17
// #define ENA 5  // Enable pin for the first motor
// #define ENB 18 // Enable pin for the second motor

const char *ssid = "Step";
const char *password = "@2805_1984@";
const char *URL = "ws://192.168.1.20:6969/ws";
WebSocket *_socketHandler;
ByteQueue *DataQueue = new ByteQueue();
QueueNodeData data;
size_t *len;
int counter = 0;
void setup()
{
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected");
  _socketHandler = new WebSocket(URL, DataQueue);
  Serial.println("Established");
  // Sensors::SetupUltrasonic();
  // pinMode(IN1, OUTPUT);
  // pinMode(IN2, OUTPUT);
  // pinMode(IN3, OUTPUT);
  // pinMode(IN4, OUTPUT);
  // RoverMovement::SetSpeed(150);
}

void loop()
{
  Serial.println("Hello World");
  if (!DataQueue->isEmpty())
  {
    Serial.println("Empy Panic");
    data = DataQueue->dequeue();
    if (data.data == nullptr)
    {
      Serial.println("Null Panic");
    }
    else
    {
      Serial.write(data.data, data.length);
      delete[] data.data;
    }
  }
  if (counter < 5)
  {
    Serial.println("Wowo NicePanic");
    _socketHandler->SendText("World Hello", 11);
    counter++;
    delay(200);
  }
  // SensorsReading r = Sensors::Ultrasonic_Read();
  // Serial.println(r.x);
  // RoverMovement::Forward();
  // RoverMovement::SelfDriving(5000);
  // Serial.println("End of loop");
  // Add any additional logic or control you need here

  // delay(1000);  // Run the motors for 1 second

  // Stop the motors
  // RoverMovement::Stop();

  delay(1000); // Pause for 1 second before running the motors again
}

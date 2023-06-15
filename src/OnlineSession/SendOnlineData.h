#ifndef SEND_ONLINE_DATA_H
#define SEND_ONLINE_DATA_H

#include "StructPlan.h"
#include "Command/Sensors.h"
#include "Serialization/Serialization.h"
#include "Command/CameraUART.h"
#include "Communication/WebSocket.h"
#include <Arduino.h>

#define SENSOR_ZERO_PADDING 3
#define DATA_SIZE 13
#define EndLine 1

#define TEMPERATURE_ID 0
#define HUMIDITY_ID 1
#define ACCELEROMETER_ID 2
#define GYROSCOPE_ID 3
#define MPU_TEMPERATURE_ID 4
#define ULTRASONIC_ID 5

class SendOnlineData
{
private:
    SensorsReading SensorData;
    StructBodyData Data;
    WebSocket *_dataSocket;

    byte *SendTemperature();
    byte *SendHumidity();
    byte *SendAccelerometer();
    byte *SendGyroscope();
    byte *SendMPUTemperature();
    byte *SendUltrasonic();
    // this method is not implemented yet

public:
    SendOnlineData();
    ~SendOnlineData();

    void SetSocket(WebSocket *dataSocket);
    void SendCamera();
    byte *SendData(byte ReadingsTurn);
};
#endif
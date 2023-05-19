#ifndef SEND_ONLINE_DATA_H
#define SEND_ONLINE_DATA_H

#include "StructPlan.h"
#include "Command/Sensors.h"
#include "Serialization/Serialization.h"
#include "Command/CameraUART.h"
#include <Arduino.h>

#define SENSOR_ZERO_PADDING 3
#define DATA_SIZE 13

class SendOnlineData
{
private:
    SensorsReading SensorData;
    StructBodyData Data;

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

    void SendCamera();
    byte *SendData(byte ReadingsTurn);
};
#endif
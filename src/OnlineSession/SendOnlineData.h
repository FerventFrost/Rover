#ifndef SEND_ONLINE_DATA_H
#define SEND_ONLINE_DATA_H

#include "StructPlan.h"
#include "Command/Sensors.h"
#include "Serialization/Serialization.h"
#include <Arduino.h>

#define SENSOR_ZERO_PADDING 3

class SendOnlineData
{
private:
    SensorsReading SensorData;
    byte *SensorDataSerialization;
    StructBodyData Data;
    byte *SendTemperature();
    byte *SendHumidity();
    byte *SendAccelerometer();
    byte *SendGyroscope();
    byte *SendMPUTemperature();
    byte *SendUltrasonic();
    // this method is not implemented yet
    void SendCamera();

public:
    SendOnlineData();
    ~SendOnlineData();

    byte *SendData();
};
#endif
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
    void SendTemperature();
    void SendHumidity();
    void SendAccelerometer();
    void SendGyroscope();
    void SendMPUTemperature();
    void SendUltrasonic();
    // this method is not implemented yet
    void SendCamera();

public:
    SendOnlineData();
    ~SendOnlineData();

    void SendData();
};
#endif
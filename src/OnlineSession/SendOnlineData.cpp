#include "SendOnlineData.h"

SendOnlineData::SendOnlineData()
{
}

SendOnlineData::~SendOnlineData()
{
}

// use must delete the returned pointer
byte *SendOnlineData::SendTemperature()
{
    SensorData = Sensors::ReadTemp();
    Data.PlanID = 0;
    Data.SequenceID = 0;
    Data.Time = esp_timer_get_time();
    Data.X = SensorData.x;
    Data.Y = 0;
    Data.Z = 0;
    SensorDataSerialization = Serialization::SerializeBodyData(&Data);
    // Serialize
    // Save to SD card
    return SensorDataSerialization;
}

// use must delete the returned pointer
byte *SendOnlineData::SendHumidity()
{
    SensorData = Sensors::ReadHumidity();
    Data.PlanID = 0;
    Data.SequenceID = 1;
    Data.Time = esp_timer_get_time();
    Data.X = SensorData.x;
    Data.Y = 0;
    Data.Z = 0;
    SensorDataSerialization = Serialization::SerializeBodyData(&Data);
    // Serialize
    // Save to SD card
    return SensorDataSerialization;
}

// use must delete the returned pointer
byte *SendOnlineData::SendAccelerometer()
{
    SensorData = Sensors::MPU_Accel();
    Data.PlanID = 0;
    Data.SequenceID = 0;
    Data.Time = esp_timer_get_time();
    Data.X = SensorData.x;
    Data.Y = SensorData.y;
    Data.Z = SensorData.z;
    SensorDataSerialization = Serialization::SerializeBodyData(&Data);
    // Serialize
    // Save to SD card
    return SensorDataSerialization;
}

// use must delete the returned pointer
byte *SendOnlineData::SendGyroscope()
{
    SensorData = Sensors::MPU_Gyro();
    Data.PlanID = 0;
    Data.SequenceID = 1;
    Data.Time = esp_timer_get_time();
    Data.X = SensorData.x;
    Data.Y = SensorData.y;
    Data.Z = SensorData.z;
    SensorDataSerialization = Serialization::SerializeBodyData(&Data);
    // Serialize
    // Save to SD card
    return SensorDataSerialization;
}

// use must delete the returned pointer
byte *SendOnlineData::SendMPUTemperature()
{
    SensorData = Sensors::MPU_Temp();
    Data.PlanID = 0;
    Data.SequenceID = 2;
    Data.Time = esp_timer_get_time();
    Data.X = SensorData.x;
    Data.Y = 0;
    Data.Z = 0;
    SensorDataSerialization = Serialization::SerializeBodyData(&Data);
    // Serialize
    // Save to SD card
    return SensorDataSerialization;
}

// use must delete the returned pointer
byte *SendOnlineData::SendUltrasonic()
{
    SensorData = Sensors::Ultrasonic_Read();
    Data.PlanID = 0;
    Data.SequenceID = 0;
    Data.Time = esp_timer_get_time();
    Data.X = SensorData.x;
    Data.Y = 0;
    Data.Z = 0;
    SensorDataSerialization = Serialization::SerializeBodyData(&Data);
    // Serialize
    // Save to SD card
    return SensorDataSerialization;
}

// use must delete the returned pointer static unsigned int i = 0; is used to keep track of the last sent data and using static keyword to keep the value of i between function calls
byte *SendOnlineData::SendData()
{
    static unsigned int i = 0;
    switch (i)
    {
    case 0:
        i++;
        return SendTemperature();

    case 1:
        i++;
        return SendHumidity();

    case 2:
        i++;
        return SendAccelerometer();

    case 3:
        i++;
        return SendGyroscope();

    case 4:
        i++;
        return SendMPUTemperature();

    case 5:
        i++;
        return SendUltrasonic();

    default:
        i++;
        return SendTemperature();
    }
}
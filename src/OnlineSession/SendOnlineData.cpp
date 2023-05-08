#include "SendOnlineData.h"

SendOnlineData::SendOnlineData()
{
}

SendOnlineData::~SendOnlineData()
{
}

void SendOnlineData::SendTemperature()
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
    delete[] SensorDataSerialization;
}

void SendOnlineData::SendHumidity()
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
    delete[] SensorDataSerialization;
}

void SendOnlineData::SendAccelerometer()
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
    delete[] SensorDataSerialization;
}

void SendOnlineData::SendGyroscope()
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
    delete[] SensorDataSerialization;
}

void SendOnlineData::SendMPUTemperature()
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
    delete[] SensorDataSerialization;
}

void SendOnlineData::SendUltrasonic()
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
    delete[] SensorDataSerialization;
}

void SendOnlineData::SendData()
{
    SendTemperature();
    SendHumidity();
    SendAccelerometer();
    SendGyroscope();
    SendMPUTemperature();
    SendUltrasonic();
}
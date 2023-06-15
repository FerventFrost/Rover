#include "SendOnlineData.h"

SendOnlineData::SendOnlineData()
{
}

SendOnlineData::~SendOnlineData()
{
}

void SendOnlineData::SetSocket(WebSocket *dataSocket)
{
    _dataSocket = dataSocket;
}
// use must delete the returned pointer
byte *SendOnlineData::SendTemperature()
{
    // Init Array
    byte *SensorDataSerialization = new byte[DATA_SIZE + SENSOR_ZERO_PADDING];
    byte *HeaderSerialization = new byte[HEADER_SIZE];
    byte *Concat = new byte[HEADER_SIZE + DATA_SIZE + SENSOR_ZERO_PADDING];
    byte *testCopy = new byte[13];
    // Body Data
    //  SensorData = Sensors::ReadTemp();
    Data.PlanID = 7;
    Data.SequenceID = TEMPERATURE_ID;
    Data.Time = esp_timer_get_time();
    Data.X = 50;
    Data.Y = 0;
    Data.Z = 1;
    SensorDataSerialization = Serialization::SerializeBodyData(&Data);
    // // Data Zero Padding
    for (int i = 0; i < SENSOR_ZERO_PADDING; i++)
        SensorDataSerialization[DATA_SIZE + i] = 0;

    // Header Data
    StructHeader Header;
    Header.Type = FrameType::Data;
    Header.FrameLength = (DATA_SIZE + SENSOR_ZERO_PADDING);
    Header.CRC = Serialization::CalculateCRC(SensorDataSerialization, DATA_SIZE);
    // Data IV
    for (int i = 0; i < 16; i++)
    {
        Header.IV[i] = 0;
    }
    HeaderSerialization = Serialization::SerializeHeader(&Header);

    Concat = Serialization::HeaderBodyConcatenate(HeaderSerialization, SensorDataSerialization, DATA_SIZE + SENSOR_ZERO_PADDING);
    delete[] SensorDataSerialization;
    delete[] HeaderSerialization;

    return Concat;
}

// use must delete the returned pointer
byte *SendOnlineData::SendHumidity()
{
    // Init Array
    byte *SensorDataSerialization = new byte[DATA_SIZE + SENSOR_ZERO_PADDING];
    byte *HeaderSerialization = new byte[HEADER_SIZE];
    byte *Concat = new byte[HEADER_SIZE + DATA_SIZE + SENSOR_ZERO_PADDING + EndLine];

    // Body Data
    SensorData = Sensors::ReadHumidity();
    Data.PlanID = 0;
    Data.SequenceID = HUMIDITY_ID;
    Data.Time = esp_timer_get_time();
    Data.X = SensorData.x;
    Data.Y = 0;
    Data.Z = 0;
    SensorDataSerialization = Serialization::SerializeBodyData(&Data);
    // Data Zero Padding
    for (int i = 0; i < SENSOR_ZERO_PADDING; i++)
        SensorDataSerialization[DATA_SIZE + i] = 0;

    // Header Data
    StructHeader Header;
    Header.Type = FrameType::Data;
    Header.FrameLength = (DATA_SIZE + SENSOR_ZERO_PADDING);
    Header.CRC = Serialization::CalculateCRC(SensorDataSerialization, DATA_SIZE);
    // Data IV
    for (int i = 0; i < 16; i++)
    {
        Header.IV[i] = 0;
    }
    HeaderSerialization = Serialization::SerializeHeader(&Header);

    // Concat Them
    Concat = Serialization::HeaderBodyConcatenate(HeaderSerialization, SensorDataSerialization, DATA_SIZE + SENSOR_ZERO_PADDING);

    delete[] SensorDataSerialization;
    delete[] HeaderSerialization;

    return Concat;
}

// use must delete the returned pointer
byte *SendOnlineData::SendAccelerometer()
{
    // Init Array
    byte *SensorDataSerialization = new byte[DATA_SIZE + SENSOR_ZERO_PADDING];
    byte *HeaderSerialization = new byte[HEADER_SIZE];
    byte *Concat = new byte[HEADER_SIZE + DATA_SIZE + SENSOR_ZERO_PADDING + EndLine];

    // Body Data
    SensorData = Sensors::MPU_Accel();
    Data.PlanID = 0;
    Data.SequenceID = ACCELEROMETER_ID;
    Data.Time = esp_timer_get_time();
    Data.X = SensorData.x;
    Data.Y = SensorData.y;
    Data.Z = SensorData.z;
    SensorDataSerialization = Serialization::SerializeBodyData(&Data);
    // Data Zero Padding
    for (int i = 0; i < SENSOR_ZERO_PADDING; i++)
        SensorDataSerialization[DATA_SIZE + i] = 0;

    // Header Data
    StructHeader Header;
    Header.Type = FrameType::Data;
    Header.FrameLength = (DATA_SIZE + SENSOR_ZERO_PADDING);
    Header.CRC = Serialization::CalculateCRC(SensorDataSerialization, DATA_SIZE);
    // Data IV
    for (int i = 0; i < 16; i++)
    {
        Header.IV[i] = 0;
    }
    HeaderSerialization = Serialization::SerializeHeader(&Header);

    // Concat Them
    Concat = Serialization::HeaderBodyConcatenate(HeaderSerialization, SensorDataSerialization, DATA_SIZE + SENSOR_ZERO_PADDING);

    delete[] SensorDataSerialization;
    delete[] HeaderSerialization;

    return Concat;
}

// use must delete the returned pointer
byte *SendOnlineData::SendGyroscope()
{
    // Init Array
    byte *SensorDataSerialization = new byte[DATA_SIZE + SENSOR_ZERO_PADDING];
    byte *HeaderSerialization = new byte[HEADER_SIZE];
    byte *Concat = new byte[HEADER_SIZE + DATA_SIZE + SENSOR_ZERO_PADDING + EndLine];

    // Body Data
    SensorData = Sensors::MPU_Gyro();
    Data.PlanID = 0;
    Data.SequenceID = GYROSCOPE_ID;
    Data.Time = esp_timer_get_time();
    Data.X = SensorData.x;
    Data.Y = SensorData.y;
    Data.Z = SensorData.z;
    SensorDataSerialization = Serialization::SerializeBodyData(&Data);
    // Data Zero Padding
    for (int i = 0; i < SENSOR_ZERO_PADDING; i++)
        SensorDataSerialization[DATA_SIZE + i] = 0;

    // Header Data
    StructHeader Header;
    Header.Type = FrameType::Data;
    Header.FrameLength = (DATA_SIZE + SENSOR_ZERO_PADDING);
    Header.CRC = Serialization::CalculateCRC(SensorDataSerialization, DATA_SIZE);
    // Data IV
    for (int i = 0; i < 16; i++)
    {
        Header.IV[i] = 0;
    }
    HeaderSerialization = Serialization::SerializeHeader(&Header);

    // Concat Them
    Concat = Serialization::HeaderBodyConcatenate(HeaderSerialization, SensorDataSerialization, DATA_SIZE + SENSOR_ZERO_PADDING);

    delete[] SensorDataSerialization;
    delete[] HeaderSerialization;

    return Concat;
}

// use must delete the returned pointer
byte *SendOnlineData::SendMPUTemperature()
{
    // Init Array
    byte *SensorDataSerialization = new byte[DATA_SIZE + SENSOR_ZERO_PADDING];
    byte *HeaderSerialization = new byte[HEADER_SIZE];
    byte *Concat = new byte[HEADER_SIZE + DATA_SIZE + SENSOR_ZERO_PADDING + EndLine];

    // Body Data
    SensorData = Sensors::MPU_Temp();
    Data.PlanID = 0;
    Data.SequenceID = MPU_TEMPERATURE_ID;
    Data.Time = esp_timer_get_time();
    Data.X = SensorData.x;
    Data.Y = 0;
    Data.Z = 0;
    SensorDataSerialization = Serialization::SerializeBodyData(&Data);
    // Data Zero Padding
    for (int i = 0; i < SENSOR_ZERO_PADDING; i++)
        SensorDataSerialization[DATA_SIZE + i] = 0;

    // Header Data
    StructHeader Header;
    Header.Type = FrameType::Data;
    Header.FrameLength = (DATA_SIZE + SENSOR_ZERO_PADDING);
    Header.CRC = Serialization::CalculateCRC(SensorDataSerialization, DATA_SIZE);
    // Data IV
    for (int i = 0; i < 16; i++)
    {
        Header.IV[i] = 0;
    }
    HeaderSerialization = Serialization::SerializeHeader(&Header);

    // Concat Them
    Concat = Serialization::HeaderBodyConcatenate(HeaderSerialization, SensorDataSerialization, DATA_SIZE + SENSOR_ZERO_PADDING);

    delete[] SensorDataSerialization;
    delete[] HeaderSerialization;

    return Concat;
}

// use must delete the returned pointer
byte *SendOnlineData::SendUltrasonic()
{
    // Init Array
    byte *SensorDataSerialization = new byte[DATA_SIZE + SENSOR_ZERO_PADDING];
    byte *HeaderSerialization = new byte[HEADER_SIZE];
    byte *Concat = new byte[HEADER_SIZE + DATA_SIZE + SENSOR_ZERO_PADDING + EndLine];

    // Body Data
    SensorData = Sensors::Ultrasonic_Read();
    Data.PlanID = 0;
    Data.SequenceID = ULTRASONIC_ID;
    Data.Time = esp_timer_get_time();
    Data.X = SensorData.x;
    Data.Y = 0;
    Data.Z = 0;
    SensorDataSerialization = Serialization::SerializeBodyData(&Data);
    // Data Zero Padding
    for (int i = 0; i < SENSOR_ZERO_PADDING; i++)
        SensorDataSerialization[DATA_SIZE + i] = 0;

    // Header Data
    StructHeader Header;
    Header.Type = FrameType::Data;
    Header.FrameLength = (DATA_SIZE + SENSOR_ZERO_PADDING);
    Header.CRC = Serialization::CalculateCRC(SensorDataSerialization, DATA_SIZE);
    // Data IV
    for (int i = 0; i < 16; i++)
    {
        Header.IV[i] = 0;
    }
    HeaderSerialization = Serialization::SerializeHeader(&Header);

    // Concat Them
    Concat = Serialization::HeaderBodyConcatenate(HeaderSerialization, SensorDataSerialization, DATA_SIZE + SENSOR_ZERO_PADDING);

    delete[] SensorDataSerialization;
    delete[] HeaderSerialization;

    return Concat;
}

// Send Camera Config Data Using UART
void SendOnlineData::SendCamera()
{
    StructBodyImage Image;
    Image.PlanID = 0;
    Image.SequenceID = 0;
    Image.OperationType = 1;

    CameraUART::SendUARTData(&Image);
}

// use must delete the returned pointer static unsigned int i = 0; is used to keep track of the last sent data and using static keyword to keep the value of i between function calls
byte *SendOnlineData::SendData(byte ReadingsTurn)
{
    switch (ReadingsTurn)
    {
    case 0:
        return SendTemperature();

    case 1:
        return SendHumidity();

    case 2:
        return SendAccelerometer();

    case 3:
        return SendGyroscope();

    case 4:
        return SendMPUTemperature();

    case 5:
        return SendUltrasonic();

    default:
        return SendTemperature();
    }
}
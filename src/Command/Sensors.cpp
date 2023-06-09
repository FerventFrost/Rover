#include "Sensors.h"

DHTesp Sensors::dhtSensor;

// MPU
void Sensors::SetupMPU()
{ 
    dhtSensor.setup(DHT_PIN, DHTesp::DHT11);
    Wire.begin();
    Wire.beginTransmission(MPU);
    Wire.write(MPU_REGISTER);
    Wire.write(RESETMPU);
    Wire.endTransmission(END_TRANSMISSION);
}

SensorsReading Sensors::MPU_Accel()
{
    SensorsReading Result;
    Wire.beginTransmission(MPU);
    Wire.write(MPU_ACCEL_REGISTER);
    Wire.endTransmission(!END_TRANSMISSION);
    Wire.requestFrom(MPU, MPU_ARRAY_SIZE_1, SEND_STOP);

    if (Wire.available() != MPU_NOT_AVAILABLE)
    {
        Result.x = (Wire.read() << 8 | Wire.read()) / 2048.0;
        Result.y = (Wire.read() << 8 | Wire.read()) / 2048.0;
        Result.z = (Wire.read() << 8 | Wire.read()) / 2048.0;
    }
    else
    {
        Result.x = -9999;
        Result.y = -9999;
        Result.z = -9999;
    }
    return Result;
}

SensorsReading Sensors::MPU_Gyro()
{
    SensorsReading Result;
    Wire.beginTransmission(MPU);
    Wire.write(MPU_GYRO_REGISTER);
    Wire.endTransmission((!END_TRANSMISSION));
    Wire.requestFrom(MPU, MPU_ARRAY_SIZE_1, SEND_STOP);

    if (Wire.available() != MPU_NOT_AVAILABLE)
    {
        Result.x = (Wire.read() << 8 | Wire.read()) / 65.5;
        Result.y = (Wire.read() << 8 | Wire.read()) / 65.5;
        Result.z = (Wire.read() << 8 | Wire.read()) / 65.5;
    }
    else
    {
        Result.x = -9999;
        Result.y = -9999;
        Result.z = -9999;
    }
    return Result;
}

SensorsReading Sensors::MPU_Temp()
{
    SensorsReading Result;
    Wire.beginTransmission(MPU);
    Wire.write(MPU_TEMP_REGISTER);
    Wire.endTransmission((!END_TRANSMISSION));
    Wire.requestFrom(MPU, MPU_ARRAY_SIZE_2, SEND_STOP);

    if (Wire.available() != MPU_NOT_AVAILABLE)
    {
        Result.x = (Wire.read() << 8 | Wire.read()) / 340 + 36.53;
        Result.y = 0;
        Result.z = 0;
    }
    else
    {
        Result.x = -9999;
        Result.y = 0;
        Result.z = 0;
    }
    return Result;
}

SensorsReading Sensors::MPU_Read(byte CommandID)
{
    if (CommandID == MPU_ACCEL)
        return Sensors::MPU_Accel();
    else if (CommandID == MPU_GYRO)
        return Sensors::MPU_Gyro();
    return Sensors::MPU_Temp();
}

// DHT
void Sensors::SetupDHT()
{
    Sensors::dhtSensor.setup(DHT_PIN, DHTesp::DHT11);
}

SensorsReading Sensors::ReadTemp()
{
    SensorsReading Result;
    Result.x = dhtSensor.getTemperature();
    Result.y = 0;
    Result.z = 0;
    if (Result.x > 255)
        Result.x = 255;
    return Result;
}

SensorsReading Sensors::ReadHumidity()
{
    SensorsReading Result;
    Result.x = dhtSensor.getHumidity();
    Result.y = 0;
    Result.z = 0;
    if (Result.x > 255)
        Result.x = 255;
    return Result;
}

SensorsReading Sensors::DHT_Read(byte CommandID)
{
    if (CommandID == DHT_TEMP)
        return ReadTemp();
    return ReadHumidity();
}

// Ultrasonic
void Sensors::SetupUltrasonic()
{
    pinMode(ULTRASONIC_TRIG_PIN, OUTPUT);
    pinMode(ULTRASONIC_ECHO_PIN, INPUT);
}

SensorsReading Sensors::Ultrasonic_Read()
{
    SensorsReading Result;
    digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(ULTRASONIC_TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
    Result.x = pulseIn(ULTRASONIC_ECHO_PIN, HIGH);
    Result.x = Result.x * 0.034 / 2;
    Result.y = 0;
    Result.z = 0;

    if (Result.x > 255)
        Result.x = 255;
    return Result;
}
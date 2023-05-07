#include "Sensors.h"

// MPU
void Sensors::SetupMPU()
{
    Wire.begin();
    Wire.beginTransmission(Sensors::MPU);
    Wire.write(Sensors::MPU_REGISTER);
    Wire.write(Sensors::RESETMPU);
    Wire.endTransmission(Sensors::END_TRANSMISSION);
}

SensorsReading Sensors::MPU_Accel()
{
    SensorsReading Result;
    Wire.beginTransmission(Sensors::MPU);
    Wire.write(Sensors::MPU_ACCEL_REGISTER);
    Wire.endTransmission((!Sensors::END_TRANSMISSION));
    Wire.requestFrom(Sensors::MPU, Sensors::MPU_ARRAY_SIZE_1, Sensors::SEND_STOP);

    if (Wire.available() != Sensors::MPU_NOT_AVAILABLE)
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
    Wire.beginTransmission(Sensors::MPU);
    Wire.write(Sensors::MPU_GYRO_REGISTER);
    Wire.endTransmission((!Sensors::END_TRANSMISSION));
    Wire.requestFrom(Sensors::MPU, Sensors::MPU_ARRAY_SIZE_1, Sensors::SEND_STOP);

    if (Wire.available() != Sensors::MPU_NOT_AVAILABLE)
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
    Wire.beginTransmission(Sensors::MPU);
    Wire.write(Sensors::MPU_TEMP_REGISTER);
    Wire.endTransmission((!Sensors::END_TRANSMISSION));
    Wire.requestFrom(Sensors::MPU, Sensors::MPU_ARRAY_SIZE_2, Sensors::SEND_STOP);

    if (Wire.available() != Sensors::MPU_NOT_AVAILABLE)
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
    Result.x = Sensors::dhtSensor.getTemperature();
    if (Result.x > 255)
        Result.x = 255;
    return Result;
}

SensorsReading Sensors::ReadHumidity()
{
    SensorsReading Result;
    Result.x = Sensors::dhtSensor.getHumidity();
    if (Result.x > 255)
        Result.x = 255;
    return Result;
}

SensorsReading Sensors::DHT_Read(byte CommandID)
{
    if (CommandID == DHT_TEMP)
        return Sensors::ReadTemp();
    return Sensors::ReadHumidity();
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

    if (Result.x > 255)
        Result.x = 255;
    return Result;
}
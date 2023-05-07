#ifndef Sensors_h
#define Sensors_h
#include "DHTesp.h"
#include <Wire.h>
#include "Arduino.h"

#define DHT_TEMP 0
#define DHT_HUMIDITY 1
#define MPU_ACCEL 0
#define MPU_GYRO 1
#define MPU_TEMP 2

#define ULTRASONIC_TRIG_PIN 13
#define ULTRASONIC_ECHO_PIN 12

struct SensorsReading
{
    short x;
    short y;
    short z;
};

class Sensors
{
private:
    static const byte MPU_NOT_AVAILABLE = 0x00;
    static const byte MPU = 0x68;
    static const byte MPU_REGISTER = 0x6B;
    static const byte MPU_ACCEL_REGISTER = 0x3B;
    static const byte MPU_GYRO_REGISTER = 0x43;
    static const byte MPU_TEMP_REGISTER = 0x41;
    static const byte RESETMPU = 0x00;
    static const byte DHT_PIN = 15;
    static const byte MPU_ARRAY_SIZE_1 = 6;
    static const byte MPU_ARRAY_SIZE_2 = 2;
    static const bool SEND_STOP = true;
    static const bool END_TRANSMISSION = true;
    static DHTesp dhtSensor;

protected:
    static SensorsReading MPU_Accel();
    static SensorsReading MPU_Gyro();
    static SensorsReading MPU_Temp();

    static SensorsReading ReadTemp();
    static SensorsReading ReadHumidity();

public:
    // MPU6050 Sensor
    static void SetupMPU();
    static SensorsReading MPU_Read(byte CommandID);
    // DHT11 Sensor
    static void SetupDHT();
    static SensorsReading DHT_Read(byte CommandID);
    // Ultrasonic Sensor
    static void SetupUltrasonic();
    static SensorsReading Ultrasonic_Read();
};

#endif
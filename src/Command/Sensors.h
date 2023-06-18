#ifndef Sensors_h
#define Sensors_h
#include "DHTesp.h"
#include <Wire.h>
#include "Arduino.h"

#define DHT_PIN 16
#define DHT_TEMP 0
#define DHT_HUMIDITY 1

#define MPU_ACCEL 0
#define MPU_GYRO 1
#define MPU_TEMP 2

#define MPU_NOT_AVAILABLE 0x00
#define MPU 0x68
#define MPU_REGISTER 0x6B
#define MPU_ACCEL_REGISTER 0x3B
#define MPU_GYRO_REGISTER 0x43
#define MPU_TEMP_REGISTER 0x41
#define RESETMPU 0x00

#define MPU_ARRAY_SIZE_1 0x06
#define MPU_ARRAY_SIZE_2 0x02

#define SEND_STOP 1
#define END_TRANSMISSION true

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
    static DHTesp dhtSensor;

public:
    Sensors() {}
    // MPU6050 Sensor
    static void SetupMPU();
    static SensorsReading MPU_Accel();
    static SensorsReading MPU_Gyro();
    static SensorsReading MPU_Temp();
    static SensorsReading MPU_Read(byte CommandID);

    // DHT11 Sensor
    static void SetupDHT();
    static SensorsReading ReadTemp();
    static SensorsReading ReadHumidity();
    static SensorsReading DHT_Read(byte CommandID);

    // Ultrasonic Sensor
    static void SetupUltrasonic();
    static SensorsReading Ultrasonic_Read();
};

#endif
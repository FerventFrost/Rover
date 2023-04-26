#ifndef Sensors_h
#define Sensors_h
#include "DHTesp.h"
#include <Wire.h>
#include "Arduino.h"

struct MPU6050_Result {
    short x;
    short y;
    short z;
};
class Sensors {
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
    public:
        // MPU6050 Sensor
        static void SetupMPU();
        static MPU6050_Result MPU_Accel();
        static MPU6050_Result MPU_Gyro();
        static MPU6050_Result MPU_Temp();

        // DHT11 Sensor
        static void SetupDHT();
        static byte ReadTemp();
        static byte ReadHumidity();

};

#endif
#include "Sensors.h"


void Sensors::SetupMPU() {
    Wire.begin();
    Wire.beginTransmission(Sensors::MPU);
    Wire.write(Sensors::MPU_REGISTER);
    Wire.write(Sensors::RESETMPU);
    Wire.endTransmission(Sensors::END_TRANSMISSION);
}

MPU6050_Result Sensors::MPU_Accel() {
    MPU6050_Result Result;
    Wire.beginTransmission(Sensors::MPU);
    Wire.write(Sensors::MPU_ACCEL_REGISTER);
    Wire.endTransmission( (!Sensors::END_TRANSMISSION) );
    Wire.requestFrom(Sensors::MPU, Sensors::MPU_ARRAY_SIZE_1, Sensors::SEND_STOP);

    if(Wire.available() != Sensors::MPU_NOT_AVAILABLE) {
        Result.x = (Wire.read() << 8 | Wire.read()) / 2048.0;
        Result.y = (Wire.read() << 8 | Wire.read()) / 2048.0;
        Result.z = (Wire.read() << 8 | Wire.read()) / 2048.0;
    }
    else {
        Result.x = -9999;
        Result.y = -9999;
        Result.z = -9999;
    }
    return Result;
}

MPU6050_Result Sensors::MPU_Gyro() {
    MPU6050_Result Result;
    Wire.beginTransmission(Sensors::MPU);
    Wire.write(Sensors::MPU_GYRO_REGISTER);
    Wire.endTransmission( (!Sensors::END_TRANSMISSION) );
    Wire.requestFrom(Sensors::MPU, Sensors::MPU_ARRAY_SIZE_1, Sensors::SEND_STOP);

    if(Wire.available() != Sensors::MPU_NOT_AVAILABLE) {
        Result.x = (Wire.read() << 8 | Wire.read()) / 65.5 ;
        Result.y = (Wire.read() << 8 | Wire.read()) / 65.5 ;
        Result.z = (Wire.read() << 8 | Wire.read()) / 65.5 ;        
    }
    else {
        Result.x = -9999;
        Result.y = -9999;
        Result.z = -9999;
    }
    return Result;
}

MPU6050_Result Sensors::MPU_Temp() {
    MPU6050_Result Result;
    Wire.beginTransmission(Sensors::MPU);
    Wire.write(Sensors::MPU_TEMP_REGISTER);
    Wire.endTransmission( (!Sensors::END_TRANSMISSION) );
    Wire.requestFrom(Sensors::MPU, Sensors::MPU_ARRAY_SIZE_2, Sensors::SEND_STOP);

    if(Wire.available() != Sensors::MPU_NOT_AVAILABLE) {
        Result.x = (Wire.read() << 8 | Wire.read()) / 340 + 36.53;
        Result.y = 0;
        Result.z = 0;
    }
    else {
        Result.x = -9999;
        Result.y = 0;
        Result.z = 0;
    }
    return Result;
}

void Sensors::SetupDHT() {
    Sensors::dhtSensor.setup(DHT_PIN, DHTesp::DHT11);
}

byte Sensors::ReadTemp() {
    short Temp = Sensors::dhtSensor.getTemperature();
    if(Temp > 255)
        return 255;
    return Temp;
}

byte Sensors::ReadHumidity() {
    short Hum = Sensors::dhtSensor.getHumidity();
    if(Hum > 255)
        return 255;
    return Hum;
}
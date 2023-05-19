#ifndef CAMERA_UART_H
#define CAMERA_UART_H

#include "StructPlan.h"
#include "Serialization/Serialization.h"
#include <Arduino.h>
#include <HardwareSerial.h>

#define TXD_PIN 17
#define RXD_PIN 16
#define IMAGE_SIZE 8

class CameraUART
{
private:
    static HardwareSerial *CameraSerial;

public:
    CameraUART();
    ~CameraUART();
    static void SetupUART();
    static void SendUARTData(StructBodyImage *Image);
};

#endif
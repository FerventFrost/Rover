#ifndef CAMERA_UART_H
#define CAMERA_UART_H

#include "StructPlan.h"
#include "Serialization/Serialization.h"
#include <Arduino.h>
#include <HardwareSerial.h>

#define BAUD_RATE 115200
#define TXD_PIN 17
#define RXD_PIN 16
#define IMAGE_SIZE 4

class CameraUART
{
private:
public:
    static void SetupUART();
    static void SendUARTData(StructBodyImage *Image);
};

#endif
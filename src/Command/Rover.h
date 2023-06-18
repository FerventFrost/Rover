#ifndef ROVER_H
#define ROVER_H

#include "Command\Sensors.h"
#include <Arduino.h>
#define BAHER_SIZE 31
#define ENA 5
#define ENB 18
#define MOTOR1 2
#define MOTOR2 4
#define MOTOR3 15
#define MOTOR4 17

class RoverMovement
{
private:

public:
    // static void SetupUltraSonic();
    // static byte ReadUltraSonic();
    static void SelfDriving(uint32_t MoveTime);
    static void SetSpeed(int speed);
    static void Forward();
    static void Backward();
    static void Right();
    static void Left();
    static void Stop();
};
#endif
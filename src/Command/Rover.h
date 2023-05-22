#ifndef ROVER_H
#define ROVER_H

#include <Arduino.h>
#define ENA 3
#define ENB 11
#define MOTOR1 5
#define MOTOR2 6
#define MOTOR3 9
#define MOTOR4 10
#define ULTRASONIC_TRIG_PIN 13
#define ULTRASONIC_ECHO_PIN 12

class RoverMovement
{
private:
    static void SetupUltraSonic();
    static byte ReadUltraSonic();

public:
    static void SelfDriving(uint32_t MoveTime);
    static void SetSpeed(int speed);
    static void Forward();
    static void Backward();
    static void Right();
    static void Left();
    static void Stop();
};
#endif
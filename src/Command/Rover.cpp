#include "Rover.h"

void RoverMovement::SetSpeed(int speed)
{
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
}

void RoverMovement::Forward()
{
    digitalWrite(MOTOR1, HIGH);
    digitalWrite(MOTOR2, LOW);
    digitalWrite(MOTOR3, HIGH);
    digitalWrite(MOTOR4, LOW);
}

void RoverMovement::Backward()
{
    digitalWrite(MOTOR1, LOW);
    digitalWrite(MOTOR2, HIGH);
    digitalWrite(MOTOR3, LOW);
    digitalWrite(MOTOR4, HIGH);
}

void RoverMovement::Right()
{
    digitalWrite(MOTOR1, LOW);
    digitalWrite(MOTOR2, HIGH);
    digitalWrite(MOTOR3, HIGH);
    digitalWrite(MOTOR4, LOW);
}

void RoverMovement::Left()
{
    digitalWrite(MOTOR1, HIGH);
    digitalWrite(MOTOR2, LOW);
    digitalWrite(MOTOR3, LOW);
    digitalWrite(MOTOR4, HIGH);
}

void RoverMovement::Stop()
{

    digitalWrite(MOTOR1, LOW);
    digitalWrite(MOTOR2, LOW);
    digitalWrite(MOTOR3, LOW);
    digitalWrite(MOTOR4, LOW);
}

void RoverMovement::SelfDriving(uint32_t MoveTime)
{
    byte reading = 0;
    unsigned long startTime = millis();
    while (millis() - startTime < MoveTime)
    {
        reading = ReadUltraSonic();
        if (reading < 30)
        {
            Stop();
            delay(1000);
            Right();
            delay(1000);
        }
        else
        {
            Forward();
        }
    }
}

void RoverMovement::SetupUltraSonic()
{
    pinMode(ULTRASONIC_TRIG_PIN, OUTPUT);
    pinMode(ULTRASONIC_ECHO_PIN, INPUT);
}

byte RoverMovement::ReadUltraSonic()
{
    byte reading = 0;
    digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(ULTRASONIC_TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
    reading = pulseIn(ULTRASONIC_ECHO_PIN, HIGH);
    reading = reading * 0.034 / 2;
    return reading;
}

// void loop()
// {
//     // put your main code here, to run repeatedly:
//     SetSpeed(255);
//     incomingByte = Serial.read();

//     Serial.println(incomingByte);

//     switch (incomingByte)
//     {
//     case 'f':
//         Forward();
//         break;
//     case 'b':
//         Backward();
//         break;
//     case 'l':
//         Left();
//         break;
//     case 'r':
//         Right();
//         break;
//     case 's':
//         Stop();
//         break;
//     default:
//         Stop();
//         break;
//     }

//     delay(1000);
// }
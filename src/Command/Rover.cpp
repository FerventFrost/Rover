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
    SensorsReading reading;
    reading.x = BAHER_SIZE;
    unsigned long startTime = millis();
    int RightTimer = 0;
    while (millis() - startTime < MoveTime)
    {
        if (reading.x < 25)
        {
            Serial.println("Obstacle Detected");
            Stop();
            delay(100);
            while (RightTimer < 700)
            {
                Right();
                delay(100);
                RightTimer += 100;
                if(Sensors::Ultrasonic_Read().x > 25)
                {
                    break;
                }
            }
            RightTimer = 0;
        }
        else
        {
            Serial.println("No Obstacle");
            Forward();
            delay(33);
        }
        reading = Sensors::Ultrasonic_Read();
    }
}

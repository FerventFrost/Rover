#include "ExecuteOnlineCommand.h"

ExecuteOnlineCommand::ExecuteOnlineCommand(/* args */)
{
}

ExecuteOnlineCommand::~ExecuteOnlineCommand()
{
}

void ExecuteOnlineCommand::RoverMovement(byte Buffer[])
{
    Command = Serialization::DeserializeBodyOnline(Buffer);
    // rover Movement

    for (int i = 0; i < Command.CommandRepeat; i++)
    {
        if (Command.CommandID == 0)
        {
            Serial.println("Forward");
            // RoverMovement::Forward();
        }
        else if (Command.CommandID == 1)
        {
            Serial.println("Backward");
            // RoverMovement::Backward();
        }
        else if (Command.CommandID == 2)
        {
            Serial.println("Right");
            // RoverMovement::Right();
        }
        else if (Command.CommandID == 3)
        {
            Serial.println("Left");
            // RoverMovement::Left();
        }
        else if (Command.CommandID == 4)
        {
            Serial.println("Stop");
            // RoverMovement::Stop();
        }
        else if (Command.CommandID == 5)
            RoverMovement::SelfDriving(5000);

        delay(Command.Delay * 500);
    }
}
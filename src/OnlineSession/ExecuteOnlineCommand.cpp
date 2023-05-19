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
            RoverMovement::Forward();
        else if (Command.CommandID == 1)
            RoverMovement::Backward();
        else if (Command.CommandID == 2)
            RoverMovement::Right();
        else if (Command.CommandID == 3)
            RoverMovement::Left();
        else if (Command.CommandID == 4)
            RoverMovement::Stop();

        delay(Command.Delay * 500);
    }
}
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
}
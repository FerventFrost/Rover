#include "ExecuteOfflineCommand.h"

// this Constructor init the timer args
ExecuteOfflineCommand::ExecuteOfflineCommand()
{
}

// Return flase if the command ID is not valid
bool ExecuteOfflineCommand::ExecuteSensorCommand()
{
    if (Command->SequenceID > 2)
        return false;

    if (Command->SubSystemID == 0)
    {
        SensorData = Sensors::DHT_Read(Command->CommandID);
    }
    else if (Command->SubSystemID == 1)
    {
        SensorData = Sensors::MPU_Read(Command->CommandID);
    }
    else if (Command->SubSystemID == 2)
    {
        SensorData = Sensors::Ultrasonic_Read();
    }

    Data.PlanID = Command->PlanID;
    Data.SequenceID = Command->SequenceID;
    Data.Time = Command->TimeBasedCommand;
    Data.X = SensorData.x;
    Data.Y = SensorData.y;
    Data.Z = SensorData.z;
    SensorDataSerialization = Serialization::SerializeBodyData(&Data);
    // Serialize
    // Save to SD card
    delete[] SensorDataSerialization;

    return true;
}

// Return flase if the command ID is not valid
bool ExecuteOfflineCommand::ExecuteCameraCommand()
{
    if (Command->SequenceID != 5)
        return false;
    // Camera
    // Serialize
    // Save to SD card

    return true;
}

// Return flase if the command ID is not valid
bool ExecuteOfflineCommand::ExecuteRoverCommand()
{
    if (Command->SequenceID != 7)
        return false;
    // Rover

    return true;
}

// Decide which command to execute (Sensor, Camera, Rover)
// A call back function for the timer
void ExecuteOfflineCommand::ExecuteCommand()
{
    for (int i = 0; i < Command->CommandRepeat; i++)
    {
        ExecuteSensorCommand();

        ExecuteCameraCommand();

        ExecuteRoverCommand();

        delay((Command->Delay * 1000));
    }
}

void ExecuteOfflineCommand::SetCommand(StructBodyOffline *_Command)
{
    Command = _Command;
}

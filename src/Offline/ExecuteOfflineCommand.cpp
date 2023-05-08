#include "ExecuteOfflineCommand.h"

// this Constructor init the timer args
ExecuteOfflineCommand::ExecuteOfflineCommand()
{
}

void ExecuteOfflineCommand::ExecuteSensorCommand()
{
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
}

void ExecuteOfflineCommand::ExecuteCameraCommand()
{
    // Camera
    // Serialize
    // Save to SD card
}

void ExecuteOfflineCommand::ExecuteRoverCommand()
{
    // Rover
}

// Decide which command to execute (Sensor, Camera, Rover)
// A call back function for the timer
void ExecuteOfflineCommand::ExecuteCommand()
{
    for (int i = 0; i < Command->CommandRepeat; i++)
    {
        if (Command->SubSystemID <= 3)
        {
            ExecuteSensorCommand();
        }
        else if (Command->SubSystemID == 3)
        {
            ExecuteCameraCommand();
        }
        else if (Command->SubSystemID == 4)
        {
            ExecuteRoverCommand();
        }
        delay((Command->Delay * 1000));
    }
}

void ExecuteOfflineCommand::SetCommand(StructBodyOffline *_Command)
{
    Command = _Command;
}

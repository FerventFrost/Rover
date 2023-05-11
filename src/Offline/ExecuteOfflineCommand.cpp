#include "ExecuteOfflineCommand.h"

// this Constructor init the timer args
ExecuteOfflineCommand::ExecuteOfflineCommand()
{
    // Set Time when offline phase starts
    Time = esp_timer_get_time();
}

// Return flase if the command ID is not valid
bool ExecuteOfflineCommand::ExecuteSensorCommand()
{
    if (Command->SequenceID > 2)
        return false;

    if (Command->SubSystemID == 0)
        SensorData = Sensors::DHT_Read(Command->CommandID);

    else if (Command->SubSystemID == 1)
        SensorData = Sensors::MPU_Read(Command->CommandID);

    else if (Command->SubSystemID == 2)
        SensorData = Sensors::Ultrasonic_Read();

    Data.PlanID = Command->PlanID;
    Data.SequenceID = Command->SequenceID;
    Data.Time = (esp_timer_get_time() - Time);
    Data.X = SensorData.x;
    Data.Y = SensorData.y;
    Data.Z = SensorData.z;
    SensorDataSerialization = Serialization::SerializeBodyData(&Data);
    // Serialize Header and Data
    // Save to SD card
    delete[] SensorDataSerialization;

    return true;
}

// Return flase if the command ID is not valid
bool ExecuteOfflineCommand::ExecuteCameraCommand()
{
    if (Command->SequenceID != 5)
        return false;

    // Communicate with Camera through UART

    return true;
}

// Return flase if the command ID is not valid
bool ExecuteOfflineCommand::ExecuteRoverCommand()
{
    if (Command->SequenceID != 7)
        return false;
    // Rover Movement

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

// This method may be discarded in the future
void ExecuteOfflineCommand::SetCommand(StructBody *_Command)
{
    Command = _Command;
}

void ExecuteOfflineCommand::RetriveCommands(byte CommandNumber)
{
    // Retrive Commands from SD card
    // SetCommand(Commands[CommandNumber]);
}

// this should return PlanSize and as well as plan address
void ExecuteOfflineCommand::RetrivePlan(byte PlanNumber)
{
    // Retrive Plan from SD card
}

void ExecuteOfflineCommand::InitExecution(byte PlanNumber)
{
    byte PlanSize = 0;
    RetrivePlan(PlanNumber);
    for (int i = 0; i < PlanSize; i++)
    {
        RetriveCommands(i);
        ExecuteCommand();
    }
}

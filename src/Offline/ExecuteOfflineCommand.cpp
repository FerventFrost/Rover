#include "ExecuteOfflineCommand.h"

#include <iomanip>
#include <iostream>

// this Constructor init the timer args
ExecuteOfflineCommand::ExecuteOfflineCommand()
{
    // Set Time when offline phase starts
    Time = esp_timer_get_time();
    Path = new char[11];
    // Set Rover Speed
    RoverMovement::SetSpeed(255);
}

ExecuteOfflineCommand::~ExecuteOfflineCommand()
{
    delete[] Path;
}

// Return flase if the command ID is not valid
void ExecuteOfflineCommand::ExecuteSensorCommand()
{
    if (Command.SubSystemID > 2)
        return;

    if (Command.SubSystemID == 0)
        SensorData = Sensors::DHT_Read(Command.CommandID);

    else if (Command.SubSystemID == 1)
        SensorData = Sensors::MPU_Read(Command.CommandID);

    else if (Command.SubSystemID == 2)
        SensorData = Sensors::Ultrasonic_Read();

    // Body Data
    Data.PlanID = Command.PlanID;
    Data.SequenceID = Command.SequenceID;
    Data.Time = (esp_timer_get_time() - Time);
    Data.X = SensorData.x;
    Data.Y = SensorData.y;
    Data.Z = SensorData.z;

    SensorDataSerialization = Serialization::SerializeBodyData(&Data);
    for (int i = 0; i < SENSOR_ZERO_PADDING; i++)
        SensorDataSerialization[DATA_SIZE + i] = 0;

    // Header Data
    StructHeader Header;
    Header.Type = FrameType::Data;
    Header.FrameLength = (DATA_SIZE + SENSOR_ZERO_PADDING);
    Header.CRC = Serialization::CalculateCRC(SensorDataSerialization, DATA_SIZE);

    for (int i = 0; i < 16; i++)
    {
        Header.IV[i] = 0;
    }
    HeaderSerialization = Serialization::SerializeHeader(&Header);

    // Concat Them
    ConcatData = Serialization::HeaderBodyConcatenate(HeaderSerialization, SensorDataSerialization, DATA_SIZE + SENSOR_ZERO_PADDING);
    SaveData(ConcatData);

    delete[] HeaderSerialization;
    delete[] SensorDataSerialization;
    delete[] ConcatData;
}

// Return flase if the command ID is not valid
void ExecuteOfflineCommand::ExecuteCameraCommand() 
{
    if (Command.SubSystemID != 3)
        return;

    StructBodyImage Image;
    Image.PlanID = Command.PlanID;
    Image.SequenceID = Command.SequenceID;
    Image.OperationType = 0;

    CameraUART::SendUARTData(&Image);
    // Communicate with Camera through UART
}

// Return flase if the command ID is not valid
void ExecuteOfflineCommand::ExecuteRoverCommand()
{
    if (Command.SubSystemID != 4)
        return;
    // Rover Movement

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
    else if(Command.CommandID == 5)
        RoverMovement::SelfDriving(5000);
}


// Decide which command to execute (Sensor, Camera, Rover)
// A call back function for the timer
void ExecuteOfflineCommand::ExecuteCommand()
{

    for (int i = 0; i < Command.CommandRepeat; i++)
    {
        ExecuteSensorCommand();

        ExecuteCameraCommand();

        ExecuteRoverCommand();

        delay((Command.Delay * 1000));
    }
}

void ExecuteOfflineCommand::OpenFile()
{
    if (SDCard::OpenAppend(SD, Path))
    {
        File = SDCard::GetFile();
    }
}

void ExecuteOfflineCommand::CloseFile()
{
    SDCard::CloseFile(File);
}

void ExecuteOfflineCommand::SaveData(byte *SaveData)
{
    SDCard::WriteDataln(File, SaveData);
}

void ExecuteOfflineCommand::RetriveCommands()
{
    // Retrive Commands from SD card
    // SetCommand(Commands[CommandNumber]);
    Command = ESPFlash::RetriveCommands();
}

void ExecuteOfflineCommand::ResetCommandAddress()
{
    ESPFlash::SetReadAddress(0);
}

void ExecuteOfflineCommand::InitExecution(StructPlanBody *Plan)
{
    switch (Plan->NumberofPlans)
    {
    case 0:
        Path = PlanFilePath.Plan1;
        break;
    case 1:
        Path = PlanFilePath.Plan2;
        break;
    case 2:
        Path = PlanFilePath.Plan3;
        break;
    case 3:
        Path = PlanFilePath.Plan4;
        break;
    case 4:
        Path = PlanFilePath.Plan5;
        break;
    default:
        break;
    }

    OpenFile();
    for (int i = 0; i < Plan->NumberofFrames; i++)
    {
        RetriveCommands();
        ExecuteCommand();
    }
    CloseFile();
}

void ExecuteOfflineCommand::SetCommand(StructBody command)
{
    Command = command;
}
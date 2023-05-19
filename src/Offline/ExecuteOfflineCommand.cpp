#include "ExecuteOfflineCommand.h"

#include <iomanip>
#include <iostream>

void printBytesAsHex(const uint8_t *bytes, size_t length)
{
    std::cout << std::hex << std::setfill('0');
    for (size_t i = 0; i < length; ++i)
    {
        std::cout << std::setw(2) << static_cast<int>(bytes[i]) << " ";
    }
    std::cout << std::dec << std::setfill(' ') << std::endl;
}
// this Constructor init the timer args
ExecuteOfflineCommand::ExecuteOfflineCommand()
{
    // Set Time when offline phase starts
    CommandAddress = 0;
    Time = esp_timer_get_time();
}

ExecuteOfflineCommand::~ExecuteOfflineCommand()
{
}

// Return flase if the command ID is not valid
bool ExecuteOfflineCommand::ExecuteSensorCommand()
{
    if (Command.SubSystemID > 2)
        return false;

    if (Command.SubSystemID == 0)
        SensorData = Sensors::DHT_Read(Command.CommandID);

    else if (Command.SubSystemID == 1)
        SensorData = Sensors::MPU_Read(Command.CommandID);

    else if (Command.SubSystemID == 2)
        SensorData = Sensors::Ultrasonic_Read();

    // Init Array
    byte *SensorDataSerialization = new byte[DATA_SIZE + SENSOR_ZERO_PADDING];
    byte *HeaderSerialization = new byte[HEADER_SIZE];
    byte *Concat = new byte[HEADER_SIZE + DATA_SIZE + SENSOR_ZERO_PADDING];

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
    Concat = Serialization::HeaderBodyConcatenate(HeaderSerialization, SensorDataSerialization, DATA_SIZE + SENSOR_ZERO_PADDING);

    // Serialize Header and Data
    // Save to SD card

    delete[] SensorDataSerialization;
    delete[] HeaderSerialization;
    delete[] Concat;

    return true;
}

// Return flase if the command ID is not valid
bool ExecuteOfflineCommand::ExecuteCameraCommand()
{
    if (Command.SubSystemID != 5)
        return false;

    // Communicate with Camera through UART

    return true;
}

// Return flase if the command ID is not valid
bool ExecuteOfflineCommand::ExecuteRoverCommand()
{
    if (Command.SubSystemID != 7)
        return false;
    // Rover Movement

    return true;
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

void ExecuteOfflineCommand::RetriveCommands()
{
    // Retrive Commands from SD card
    // SetCommand(Commands[CommandNumber]);
    EEPROM.get(CommandAddress, Command);
    CommandAddress += sizeof(StructBody);
}

void ExecuteOfflineCommand::InitExecution(StructPlanBody *Plan)
{
    for (int i = 0; i < Plan->NumberofFrames; i++)
    {
        RetriveCommands();
        ExecuteCommand();
    }
}
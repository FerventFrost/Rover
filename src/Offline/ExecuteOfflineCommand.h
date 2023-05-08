#ifndef ExecuteOfflineCommand_h
#define ExecuteOfflineCommand_h

#include "StructPlan.h"
#include "Command/Sensors.h"
#include "Serialization/Serialization.h"
#include <Arduino.h>

#define SENSOR_ZERO_PADDING 3
#define MAX_PLAN_SIZE 15
#define MAX_DATA_SIZE 16

// This Class can't be used with threads because SensorData is a data member global variable
// INs : Take Command using SetCommand method and init timer using InitCommandTimer method
// OUTs : Execute the command and save the data to SD card
class ExecuteOfflineCommand
{
private:
    SensorsReading SensorData;
    byte *SensorDataSerialization;
    esp_timer_handle_t ExecuteCommandTimer;
    esp_timer_create_args_t timer_args;
    StructBodyOffline *Command;
    StructBodyData Data;

protected:
    void ExecuteSensorCommand();
    void ExecuteCameraCommand();
    void ExecuteRoverCommand();
    void ExecuteCommand();

public:
    ExecuteOfflineCommand();
    ~ExecuteOfflineCommand();

    void InitExecution();
    void SetCommand(StructBodyOffline *_Command);
    void RetriveCommands();
    void RetrivePlan();
};

#endif
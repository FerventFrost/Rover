#ifndef ExecuteOfflineCommand_h
#define ExecuteOfflineCommand_h

#include "StructPlan.cpp"
#include "Command/Sensors.h"
#include <Arduino.h>
#include "esp_timer.h"

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
    byte SensorDataSerialization[MAX_DATA_SIZE];
    esp_timer_handle_t ExecuteCommandTimer;
    esp_timer_create_args_t timer_args;
    StructBodyOffline *Command;

protected:
    void ExecuteSensorCommand();
    void ExecuteCameraCommand();
    void ExecuteRoverCommand();

public:
    ExecuteOfflineCommand();
    ~ExecuteOfflineCommand();

    void ExecuteCommand(void *arg);
    void SetCommand(StructBodyOffline *_Command);
    void EndPlanExecution();
};
#endif
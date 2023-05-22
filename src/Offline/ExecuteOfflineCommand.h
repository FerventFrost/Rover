#ifndef ExecuteOfflineCommand_h
#define ExecuteOfflineCommand_h

#include "StructPlan.h"
#include "Command/Sensors.h"
#include "Serialization/Serialization.h"
#include "Command/Rover.h"
#include "Command/CameraUART.h"
#include "Command/ESPFlash.h"
#include "Command/SDCard.h"
#include <Arduino.h>

#define SENSOR_ZERO_PADDING 3
#define MAX_PLAN_SIZE 15
#define MAX_DATA_SIZE 16
#define DATA_SIZE 13
// This Class can't be used with threads because SensorData is a data member global variable
// INs : Take Command using SetCommand method and init timer using InitCommandTimer method
// OUTs : Execute the command and save the data to SD card
class ExecuteOfflineCommand
{
private:
    // byte *SensorDataSerialization;
    int32_t CommandAddress;
    int64_t Time;
    fs::File File;
    char *Path;
    SensorsReading SensorData;
    StructBody Command;
    StructBodyData Data;

protected:
    bool ExecuteSensorCommand();
    bool ExecuteCameraCommand();
    bool ExecuteRoverCommand();
    bool ExecuteRoverSelfDriving();
    void SetPath(char *path);
    void OpenFile();
    void CloseFile();
    void SaveData(byte *SaveData);


public:
    ExecuteOfflineCommand();
    ~ExecuteOfflineCommand();

    void ResetCommandAddress();
    void ExecuteCommand();
    void InitExecution(StructPlanBody *Plan);
    void RetriveCommands();
};

#endif
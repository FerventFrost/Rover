#ifndef EXECUTEONLINECOMMAND_H
#define EXECUTEONLINECOMMAND_H

#include "StructPlan.h"
#include "Serialization/Serialization.h"
#include "Arduino.h"

// Assocaited with rover movement and sensors configuration
class ExecuteOnlineCommand
{
private:
    /* data */
    StructBodyOnline Command;

public:
    ExecuteOnlineCommand(/* args */);
    ~ExecuteOnlineCommand();

    void RoverMovement(byte Buffer[]);
    // this class is not implemented yet
    void SensorsConfiguration(byte Buffer[]);
};
#endif
// Creator: Jeffrey Blancett on 7/9/2019
// this class will not be used till finial stages of the project
#ifndef PlanValidation_H
#define PlanValidation_H

#include "StructPlan.h"
#include "Serialization/Serialization.h"
#include "Arduino.h"

#define BODY_ONLINE_SIZE 16
class PlanValidation
{
private:
    /* data */
    StructBodyOnline Command;

public:
    PlanValidation(/* args */);
    ~PlanValidation();

    void SaveCommands();
    void ParseCommands(byte Buffer[]);
    void SavePlan();
    void ParsePlan(byte Buffer[]);
    bool isValidateCRC(byte Buffer[], unsigned int CRC);
    // this methods in not implemented yet
    bool ValidateAES(byte Buffer[]);
    bool ValidateSHA(byte Buffer[]);
};
#endif
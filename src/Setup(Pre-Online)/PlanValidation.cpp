#include "PlanValidation.h"

PlanValidation::PlanValidation(/* args */)
{
}

PlanValidation::~PlanValidation()
{
}

void PlanValidation::SaveCommands()
{
    // save commands to EEPROM
}

void PlanValidation::ParseCommands(byte Buffer[])
{
    // parse commands from EEPROM
    Command = Serialization::DeserializeBodyOnline(Buffer);
}

void PlanValidation::SavePlan()
{
    // save plan to EEPROM
}

void PlanValidation::ParsePlan(byte Buffer[])
{
    // parse plan from EEPROM
}

bool PlanValidation::isValidateCRC(byte Buffer[], unsigned int CRC)
{
    // validate plan
    if (Serialization::isValidCRC(Buffer, BODY_ONLINE_SIZE, CRC))
        return true;
    return false;
}
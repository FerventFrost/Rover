#include "AcceptPlan.h"

AcceptData::AcceptData()
{
    PlanCounter = 0;
    Plan = new StructPlanBody[PLAN_MAX];
}


void AcceptData::AcceptHeader(byte *buffer)
{
    Header = Serialization::DeserializeHeader(buffer);
}

bool AcceptData::AcceptPlan(byte *buffer)
{

    if (!Serialization::isValidCRC(buffer, 6, Header.CRC))
        return false;

    StructPlanBody plan = Serialization::DeserializePlanBody(buffer);
    Plan[PlanCounter] = plan;
    PlanCounter++;

    return true;
}

bool AcceptData::AcceptCommand(byte *buffer)
{
    if (!Serialization::isValidCRC(buffer, 7, Header.CRC))
        return false;

    StructBody command = Serialization::DeserializeBodyOnline(buffer);
    SaveCommand(command);

    return true;
}

void AcceptData::ResetCommandAdress()
{
    ESPFlash::SetWriteAddress(0);
}

// Save the command to the flash memory
void AcceptData::SaveCommand(StructBody command)
{
    ESPFlash::WriteCommand(command);
}

// Please Delete the returned pointer after use
StructPlanBody *AcceptData::ReturnPlans()
{
    return Plan;
}
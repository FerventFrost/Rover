#include "AcceptPlan.h"

AcceptData::AcceptData()
{
    PlanCounter = 0;
    Plan = new StructPlanBody[PLAN_MAX];
}

~AcceptData::AcceptData()
{
    delete[] AcceptData::Plan;
}

// void AcceptData::ListenPlan()
// {
//     // This method listen for the plan using Websocket from Ground Station
//     // Send plan is received to Ground Station as a response
//     // Parse plan's header and return it (Plan ID, Plan Length, Plan Checksum)
// }

// void AcceptData::AcceptInvalidPlan()
// {
//     // This method accept the invalid plan by sending the plan ID to Ground Station
//     // Send plan is received to Ground Station as a response
// }

// void AcceptData::StorePlan()
// {
//     // This method store the plan in the EEPROM and return the plan ID and Address
//     // Send plan is Done to Ground Station as a response
// }

// void AcceptData::EndAcceptPlan()
// {
//     // This method end the Accept Plan process by sending the plan ID to Ground Station
// }

// bool AcceptData::isPlanValid()
// {
//     // This method check if the plan is valid using the checksum
//     // and return true if the plan is valid
//     // and return false if the plan is invalid

//     // Send plan is invalid to Ground Station as a PlanResend response
//     return true;
// }

// bool AcceptData::isPlanAvailable()
// {
//     // This method check Plan Counter and return true if Plan Counter is less than or equal PLAN_MAX
//     return true;
// }

// void AcceptData::ExecuteAcceptPlan()
// {
//     // 1. Check if plan is available using isPlanAvailable()
//     // 2. If plan is available, accept the plan using AcceptPlan()
//     // 3. If plan is not available, go to step 8
//     // 4. check if plan is valid using isPlanValid()
//     // 5. If plan is valid, store the plan using StorePlan()
//     // 6. If plan is invalid, accept the invalid plan using AcceptInvalidPlan() by sending the plan ID to Ground Station and return to step 4
//     // 7. If plan is valid, return to step 1
//     // 8. End the Accept Plan process using EndAcceptPlan() by sending the plan ID to Ground Station
// }

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
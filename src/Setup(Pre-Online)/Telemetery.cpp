#include "Telemetery.h"

// // Note if Plan will save multiple commands then we need to add a command counter to the plan
// void Telemetery::RetriveTelemetery()
// {
//     // Accept Plan From SD Card using PlanAddress
// }

// void Telemetery::SendTelemetery()
// {
//     // Send Plan to Ground Station using WebSockets
// }

// void Telemetery::DeleteTelemetery()
// {
//     // Delete Plan from SD Card using PlanAddress
// }

// bool Telemetery::IsPlanAvailable()
// {
//     // Check if there is a commands that needs to be sent to the ground station in a single plan and return true
//     // if there is no command left to be sent then return false
//     return true;
// }

// bool Telemetery::NextPlan()
// {
//     // Get Next Plan Address if there is one and save it to planAddress and return true
//     // if there is no next plan then set planAddress to null and return false
//     return true;
// }

// void Telemetery::SendEndOfTelemetery()
// {
//     // At the end of the telemetery send a message to the ground station that the telemetery is over
// }

// void Telemetery::RunTelemetery()
// {
//     // 1. First check if there is a plan by calling NextPlan()
//     // 2. if there is a plan then call RetriveTelemetery()
//     // 3. then call SendTelemetery() to send the plan to the ground station using WebSockets
//     // 4. then call isPlanAvailable() to check if there is another Command to be sent in a single plan
//     // 5. if there is another command then go to step 2
//     // 6. if there is no command then call DeleteTelemetery() to delete the plan from the SD Card
//     // 7. check if there is another plan by calling NextPlan()
//     // 8. if there is another plan then go to step 2
//     // 9. if there is no plan then call SendEndOfTelemetery() to send a message to the ground station that the telemetery is over
// }

void Telemetery::SetPath(const char *path)
{
    Path = path;
}

void Telemetery::OpenFile()
{
    if (SDCard::OpenRead(SD, Path))
    {
        File = SDCard::GetFile();
    }
}

void Telemetery::CloseFile()
{
    SDCard::CloseFile(File);
}

bool Telemetery::IsFileAvailable()
{
    return SDCard::isFileAvailable(SD, File, Path);
}

byte *Telemetery::GetTelemetery()
{
    if (!SDCard::isFileAvailable(SD, File, Path))
    {
        CloseFile();
        return NULL;
    }
    return SDCard::ReadData(SD, File, Path);
}
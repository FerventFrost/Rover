#include "StateController.h"

StateController::StateController()
{
    currentState = State::TelemeteryState;
}

StateController::~StateController()
{
}
void StateController::TelemeteryState()
{
    byte PlanCounter = 1;
    bool NextPlan = true;

    // Init Telemetery
    byte *buffer = InitTelemeteryRequest();
    SendSocketData(buffer);
    delete[] buffer;
    buffer = nullptr;

    // Send All Telemetery
    while (true)
    {
        // Open the file for reading
        if (NextPlan && PlanCounter == 1)
        {
            TelemeteryInstance.SetPath(FilePaths.Plan1);
            TelemeteryInstance.OpenFile();
            PlanCounter++;
            NextPlan = false;
        }
        else if (NextPlan && PlanCounter == 2)
        {
            TelemeteryInstance.CloseFile();
            SDCard::RemoveAllData(SD, File, FilePaths.Plan1);
            TelemeteryInstance.SetPath(FilePaths.Plan2);
            TelemeteryInstance.OpenFile();
            PlanCounter++;
            NextPlan = false;
        }
        else if (NextPlan && PlanCounter == 3)
        {
            TelemeteryInstance.CloseFile();
            SDCard::RemoveAllData(SD, File, FilePaths.Plan2);
            TelemeteryInstance.SetPath(FilePaths.Plan3);
            TelemeteryInstance.OpenFile();
            PlanCounter++;
            NextPlan = false;
        }
        else if (NextPlan && PlanCounter == 4)
        {
            TelemeteryInstance.CloseFile();
            SDCard::RemoveAllData(SD, File, FilePaths.Plan3);

            TelemeteryInstance.SetPath(FilePaths.Plan4);
            TelemeteryInstance.OpenFile();
            PlanCounter++;
            NextPlan = false;
        }
        else if (NextPlan && PlanCounter == 5)
        {
            TelemeteryInstance.CloseFile();
            SDCard::RemoveAllData(SD, File, FilePaths.Plan4);
            TelemeteryInstance.SetPath(FilePaths.Plan5);
            TelemeteryInstance.OpenFile();
            PlanCounter++;
            NextPlan = false;
        }
        else if (NextPlan && PlanCounter == 6)
        {
            TelemeteryInstance.CloseFile();
            SDCard::RemoveAllData(SD, File, FilePaths.Plan5);
            byte *buffer = EndTelemetryRequest();
            SendSocketData(buffer);
            delete[] buffer;
            break;
        }
        else
            NextPlan = SendTelemetery();
    }

    currentState = State::AcceptPlanState;
}

void StateController::AcceptPlanState()
{
}

void StateController::ExecuteOnlineCommandState()
{
}

void StateController::SendOnlineDataState()
{
}

void StateController::SendSocketData(byte *buffer)
{
    // send data to socket
}

fs::File StateController::OpenFile(const char *path)
{
    // open file
    SDCard::OpenRead(SD, path);
    fs::File file = SDCard::GetFile();
    return file;
}

void StateController::CloseFile(fs::File file)
{
    // close file
    file.close();
}

void StateController::DeleteData(fs::File file, const char *path)
{
    // delete file
    SDCard::RemoveAllData(SD, File, path);
    file.close();
    SD.remove(path);
}

void StateController::CreateFile(const char *path)
{
    // create file
    SDCard::OpenAppend(SD, path);
    fs::File file = SDCard::GetFile();
    file.close();
}

bool StateController::SendTelemetery()
{
    // send telemetery
    byte *buffer = TelemeteryInstance.GetTelemetery();
    if (buffer == NULL)
    {
        delete[] buffer;
        buffer = nullptr;
        return true;
    }

    SendSocketData(buffer);
    delete[] buffer;
    buffer = nullptr;
    return false;
}
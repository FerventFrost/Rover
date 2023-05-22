#ifndef STATE_CONTROLLER_H
#define STATE_CONTROLLER_H

#include "StructPlan.h"
#include "Setup(Pre-Online)/Telemetery.h"
#include "Setup(Pre-Online)/AcceptPlan.h"
#include "OnlineSession/ExecuteOnlineCommand.h"
#include "OnlineSession/SendOnlineData.h"
#include "Command/CameraUART.h"
#include "Command/SDCard.h"
#include <Arduino.h>

enum State
{
    TelemeteryState,
    AcceptPlanState,
    ExecuteOnlineCommandState,
    SendOnlineDataState
};

struct FilePath
{
    const char *Plan1 = "Plan1.txt";
    const char *Plan2 = "Plan2.txt";
    const char *Plan3 = "Plan3.txt";
    const char *Plan4 = "Plan4.txt";
    const char *Plan5 = "Plan5.txt";
};

class StateController
{
private:
    FilePath FilePaths;
    State currentState;
    byte Packet;
    byte Header;
    byte Command;
    fs::File File;
    Telemetery TelemeteryInstance;
    AcceptData AcceptDataInstance;
    ExecuteOnlineCommand ExecuteOnlineCommandInstance;
    SendOnlineData SendOnlineDataInstance;

protected:
    byte *InitTelemeteryRequest();
    byte *EndTelemetryRequest();
    byte *InitAcceptPlanRequest();
    byte *EndAcceptPlanRequest();
    byte *InitOnlineRequest();
    byte *EndOnlineRequest();
    byte *AcceptPlanRequest();
    byte *ResendPlanRequest();

    FrameType GetFrameType(byte *buffer);
    void SendSocketData(byte *buffer);

    fs::File OpenFile(const char *path);
    void CloseFile(fs::File file);
    void CreateFile(const char *path);
    void DeleteData(fs::File file, const char *path);

    bool SendTelemetery();

public:
    StateController();
    ~StateController();

    void RunStates();
    void SetState(State state);
    void TelemeteryState();
    void AcceptPlanState();
    void ExecuteOnlineCommandState();
    void SendOnlineDataState();
};

#endif

#ifndef STATE_CONTROLLER_H
#define STATE_CONTROLLER_H

#include "StructPlan.h"
#include "Setup(Pre-Online)/Telemetery.h"
#include "Setup(Pre-Online)/AcceptPlan.h"
#include "OnlineSession/ExecuteOnlineCommand.h"
#include "OnlineSession/SendOnlineData.h"
#include "Command/CameraUART.h"
#include "Command/SDCard.h"
#include "Communication/WebSocket.h"
#include <Arduino.h>
#include <iomanip>
#include <iostream>

enum State
{
    TelemeteryState,
    AcceptPlanState,
    ExecuteOnlineCommandState,
    SendOnlineDataState
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
    WebSocket *_dataSocket;

    // void printBytesAsHex(const uint8_t *bytes, size_t length);

protected:
    // Create Request Packet
    byte *InitTelemeteryRequest();
    byte *EndTelemetryRequest();
    byte *InitAcceptPlanRequest();
    byte *EndAcceptPlanRequest();
    byte *InitOnlineRequest();
    byte *EndOnlineRequest();
    byte *AcceptPlanRequest();
    byte *DonePlanRequest();
    byte *ResendPlanRequest();

    // File Handling Methods
    fs::File OpenFile(const char *path);
    void CloseFile(fs::File file);
    void CreateFile(const char *path);
    void DeleteData(fs::File file, const char *path);

    // Socket Methods
    void SendSocketData(byte *buffer);
    byte *ReceiveSocketData();
    bool ReceivedDataQueue();

    // Telemetery Methods
    bool SendTelemetery(bool TelemeteryImage);
    void SendImageTelemetry(int PlanID, byte SequenceID);

    // Accept Plan Methods
    bool ReceivedData(StructHeader *Header, byte *buffer, bool isOnline);
    void ReceivedRequest(StructHeader *Header, byte *buffer);

public:
    StateController(WebSocket *DataSocket);
    ~StateController();

    void SetupStateMachine();
    void RunStates();
    void SetState(State state);
    void TelemeteryState();
    void AcceptPlanState();
    void OnlineState();
    bool ExecuteOnlineCommandState();
    void SendOnlineDataState();
};

#endif

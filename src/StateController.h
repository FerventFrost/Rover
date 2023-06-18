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
    Telemetery TelemeteryInstance;
    AcceptData AcceptDataInstance;
    ExecuteOnlineCommand ExecuteOnlineCommandInstance;
    SendOnlineData SendOnlineDataInstance;

    WebSocket *_dataSocket;
    ByteQueue *_dataQueue;
    FilePath FilePaths;

    State currentState;
    byte Packet;
    byte Header;
    byte Command;
    fs::File File;

protected:
    // Create Request Packet
    void _InitTelemeteryRequest();
    void _EndTelemetryRequest();
    void _InitAcceptPlanRequest();
    void _EndAcceptPlanRequest();
    void _InitOnlineRequest();
    void _EndOnlineRequest();
    void _AcceptPlanRequest();
    void _DonePlanRequest();
    void _ResendPlanRequest();

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
    StateController(WebSocket *DataSocket, ByteQueue *Queue);
    ~StateController();

    void SetupStateMachine();
    void RunStates();
    void SetState(State state);
    void TelemeteryState();
    void AcceptPlanState();
    void OnlineState();
    bool ExecuteOnlineCommandState(byte *data);
    void SendOnlineDataState();
};

#endif

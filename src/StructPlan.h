
#ifndef STRUCT_BODY_H
#define STRUCT_BODY_H
#include "Arduino.h"

// ACK doante by 1
// nonACK doante by 0
enum AckType
{
    StartSetup,
    EndSetup,
    SendTelemetry,
    EndTelemetry,
    SendPlan,
    EndPlan,
    PlanReceived,
    PlanDone,
    PlanReSend,
    StratOnline,
    EndOnline
};

enum FrameType
{
    Online,
    Offline,
    Request,
    Response,
    Data,
    Image
};

struct StructHeader
{
    FrameType Type;           // Packet Type that indicate Plan is (online, offline, request, resend, data, or image)
    unsigned int FrameLength; // Frame Length
    unsigned int CRC;         // Sum of Frame Char
    byte IV[16];              // Initialization Vector
};

// From GS to Rover
struct StructBodyOffline
{
    /* data */
    unsigned int PlanID; // Plan Number
    byte SequenceID;     // Frame Number in Plan
    byte SubSystemID;
    byte CommandID;
    byte Delay;
    byte CommandRepeat;
    unsigned long TimeBasedCommand;
};

// From GS to Rover
struct StructBodyOnline
{
    /* data */
    unsigned int PlanID; // Plan Number
    byte SequenceID;     // Frame Number in Plan
    byte SubSystemID;
    byte CommandID;
    byte Delay;
    byte CommandRepeat;
};

// From GS to Rover and Rover to GS
struct StructBodyRequest
{
    /* data */
    bool Ack;
    AckType Acktype;
};

// From Rover to GS
struct StructBodyData
{
    /* data */
    unsigned int PlanID; // Plan Number
    byte SequenceID;     // Frame Number in Plan
    unsigned long Time;
    unsigned int X;
    unsigned int Y;
    unsigned int Z;
};
// From Rover to GS
struct StructBodyImage
{
    /* data */
    short PlanID;    // Plan Number
    byte SequenceID; // Frame Number in Plan
    // Camera;
    unsigned int Time;
};

#endif
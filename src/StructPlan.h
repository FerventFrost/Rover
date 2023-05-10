
#ifndef STRUCT_BODY_H
#define STRUCT_BODY_H
#include "Arduino.h"

// ADD ACK doante by 1
// ADD nonACK doante by 0
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
    Plan,
    Command,
    Request,
    Data,
    Image
};

struct StructHeader
{
    FrameType Type;           // Packet Type that indicate Plan is (online, offline, request, resend, data, or image)
    byte IV[16];              // Initialization Vector
    unsigned int CRC;         // Sum of Frame Char
    unsigned int FrameLength; // Frame Length
};

// This is send from GS to Rover in Accept Plan Phase
struct StructPlanBody
{
    byte NumberofPlans;
    byte NumberofFrames;
    unsigned long Time;
};

// From GS to Rover
struct StructBody
{
    /* data */
    byte SequenceID; // Frame Number in Plan
    byte SubSystemID;
    byte CommandID;
    byte Delay;
    byte CommandRepeat;
    unsigned int PlanID; // Plan Number
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
    byte SequenceID;     // Frame Number in Plan
    unsigned int PlanID; // Plan Number
    unsigned int X;
    unsigned int Y;
    unsigned int Z;
    unsigned long Time;
};
// From Rover to GS
struct StructBodyImage
{
    /* data */
    byte SequenceID;     // Frame Number in Plan
    unsigned int PlanID; // Plan Number
    // Camera;
    unsigned long Time;
};

#endif

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

const struct FilePath
{
    const char *Plan1;
    const char *Plan2;
    const char *Plan3;
    const char *Plan4;
    const char *Plan5;
} PlanFilePath{"/Plan1.txt", "/Plan2.txt", "/Plan3.txt", "/Plan4.txt", "/Plan5.txt"};

// Struct Size is 21
struct StructHeader
{
    FrameType Type;       // Packet Type that indicate Plan is (online, offline, request, resend, data, or image)
    byte IV[16];          // Initialization Vector
    uint16_t CRC;         // Sum of Frame Char
    uint16_t FrameLength; // Frame Length
};

// This is send from GS to Rover in Accept Plan Phase
// Struct Size is 6
struct StructPlanBody
{
    byte NumberofPlans;
    byte NumberofFrames;
    uint32_t Time;
};

// From GS to Rover
// Struct Size is 7
struct StructBody
{
    /* data */
    byte SequenceID; // Frame Number in Plan
    byte SubSystemID;
    byte CommandID;
    byte Delay;
    byte CommandRepeat;
    uint16_t PlanID; // Plan Number
};

// From GS to Rover and Rover to GS
// Struct Size is 2
struct StructBodyRequest
{
    /* data */
    bool Ack;
    AckType Acktype;
};

// From Rover to GS
// Struct Size is 13
struct StructBodyData
{
    /* data */
    byte SequenceID; // Frame Number in Plan
    uint16_t PlanID; // Plan Number
    uint16_t X;
    uint16_t Y;
    uint16_t Z;
    uint32_t Time;
};

// From Rover to GS
struct StructBodyImage
{
    /* data */
    byte SequenceID; // Frame Number in Plan
    byte OperationType;
    uint16_t PlanID; // Plan Number
};

struct QueueNodeData
{
    byte *data;
    size_t length;
};
#endif
//
// Created by BAHER on 5/7/2023.
//

#ifndef TEST_STRUCT_H
#define TEST_STRUCT_H

#include <iostream>

/* arduino type size
 * uint8_t is byte
 * uint16_t is unsinged int
 * uint32_t is unsinged long
 * */
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
    uint16_t FrameLength; // Frame Length
    uint16_t CRC;         // Sum of Frame Char
    uint8_t IV[16];              // Initialization Vector
};

// From GS to Rover
struct StructBodyOffline
{
    /* data */
    uint16_t PlanID; // Plan Number
    uint8_t SequenceID;     // Frame Number in Plan
    uint8_t SubSystemID;
    uint8_t CommandID;
    uint8_t Delay;
    uint8_t CommandRepeat;
    uint32_t TimeBasedCommand;
};

// From GS to Rover
struct StructBodyOnline
{
    /* data */
    uint16_t PlanID; // Plan Number
    uint8_t SequenceID;     // Frame Number in Plan
    uint8_t SubSystemID;
    uint8_t CommandID;
    uint8_t Delay;
    uint8_t CommandRepeat;
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
    uint16_t PlanID; // Plan Number
    uint8_t SequenceID;     // Frame Number in Plan
    uint32_t Time;
    uint16_t X;
    uint16_t Y;
    uint16_t Z;
};
// From Rover to GS
struct StructBodyImage
{
    /* data */
    uint16_t PlanID;    // Plan Number
    uint8_t SequenceID; // Frame Number in Plan
    // Camera;
    uint32_t Time;
};

#endif //TEST_STRUCT_H

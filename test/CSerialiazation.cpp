//
// Created by BAHER on 5/7/2023.
//

#include "CSerialiazation.h"

#include "Struct.h"

// DivideShort seperate a short into 2 bytes. eg 0x1234 -> 0x12 0x34.
// You must Delete the returned pointer after use or else memory leak will occur.
uint8_t *CSerialiazation::DivideTwoByte(uint16_t value)
{
    uint8_t *bytes = new uint8_t[2];
    bytes[0] = (uint8_t)(value >> 8);
    bytes[1] = (uint8_t)(value);
    return bytes;
}

// Divide Long seperate a int into 4 bytes. eg 0x12345678 -> 0x12 0x34 0x56 0x78.
// You must Delete the returned pointer after use or else memory leak will occur.
uint8_t *CSerialiazation::DivideFourByte(uint32_t value)
{
    uint8_t *bytes = new uint8_t[4];
    bytes[0] = (uint8_t)(value >> 24);
    bytes[1] = (uint8_t)(value >> 16);
    bytes[2] = (uint8_t)(value >> 8);
    bytes[3] = (uint8_t)(value);
    return bytes;
}

// Combine Int combine 2 bytes into a short. eg 0x12 0x34 -> 0x1234.
uint16_t CSerialiazation::CombineTwoByte(uint8_t *value)
{
    uint16_t result = 0;
    result = (result << 8) + value[0];
    result = (result << 8) + value[1];
    return result;
}

// Combine Long combine 4 bytes into a int. eg 0x12 0x34 0x56 0x78 -> 0x12345678.
uint32_t CSerialiazation::CombineFourByte(uint8_t *value)
{
    uint32_t result = 0;
    result = (result << 8) + value[0];
    result = (result << 8) + value[1];
    result = (result << 8) + value[2];
    result = (result << 8) + value[3];
    return result;
}

bool CSerialiazation::isValidCRC(uint8_t *buffer, uint16_t size, uint16_t CRC)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += buffer[i];
    }
    if (sum == CRC)
        return true;
    return false;
}

uint16_t CSerialiazation::CalculateCRC(uint8_t *buffer, uint16_t size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += buffer[i];
    }
    return sum;
}

// Return a pointer to a buffer that contains the serialized header.
// You must Delete the returned pointer after use or else memory leak will occur.
uint8_t *CSerialiazation::SerializeHeader(StructHeader *Header)
{
    uint8_t *buffer = new uint8_t[(HEADER_SIZE)];
    uint8_t *temp = new uint8_t[2];
    buffer[0] = Header->Type;
    temp = DivideTwoByte(Header->FrameLength);
    buffer[1] = temp[0];
    buffer[2] = temp[1];
    temp = DivideTwoByte(Header->CRC);
    buffer[3] = temp[0];
    buffer[4] = temp[1];

    // Copy IV
    for (int i = 5; i < HEADER_SIZE; i++)
    {
        buffer[i] = Header->IV[i - 5];
    }
    return buffer;
}

// Buffer Size is 20
StructHeader CSerialiazation::DeserializeHeader(uint8_t buffer[])
{
    StructHeader Header;
    Header.Type = static_cast<FrameType>(buffer[0]);
    Header.FrameLength = CombineTwoByte(&buffer[1]);
    Header.CRC = CombineTwoByte(&buffer[3]);
    for (int i = 5; i < HEADER_SIZE; i++)
    {
        Header.IV[i - 5] = buffer[i];
    }
    return Header;
}

StructBodyOffline CSerialiazation::DeserializeBodyOffline(uint8_t buffer[])
{
    StructBodyOffline Body;
    Body.PlanID = CombineTwoByte(&buffer[0]);
    Body.SequenceID = buffer[2];
    Body.SubSystemID = buffer[3];
    Body.CommandID = buffer[4];
    Body.Delay = buffer[5];
    Body.CommandRepeat = buffer[6];
    Body.TimeBasedCommand = CombineFourByte(&buffer[7]);
    return Body;
}

StructBodyOnline CSerialiazation::DeserializeBodyOnline(uint8_t buffer[])
{
    StructBodyOnline Body;
    Body.PlanID = CombineTwoByte(&buffer[0]);
    Body.SequenceID = buffer[2];
    Body.SubSystemID = buffer[3];
    Body.CommandID = buffer[4];
    Body.Delay = buffer[5];
    Body.CommandRepeat = buffer[6];
    return Body;
}

// Return a pointer to a buffer that contains the serialized header.
// You must Delete the returned pointer after use or else memory leak will occur.
uint8_t *CSerialiazation::SerializeBodyResponse(StructBodyRequest *Request)
{
    uint8_t *buffer = new uint8_t[(REQUEST_SIZE)];
    buffer[0] = Request->Ack;
    buffer[1] = Request->Acktype;
    return buffer;
}

StructBodyRequest CSerialiazation::DeserializeBodyRequest(uint8_t buffer[])
{
    StructBodyRequest Body;
    Body.Ack = buffer[0];
    Body.Acktype = static_cast<AckType>(buffer[1]);
    return Body;
}

// Return a pointer to a buffer that contains the serialized header.
// You must Delete the returned pointer after use or else memory leak will occur.
uint8_t *CSerialiazation::SerializeBodyData(StructBodyData *Body)
{
    uint8_t *buffer = new uint8_t[(SENSOR_DATA_SIZE)];
    uint8_t *temp = new uint8_t[4];
    temp = DivideTwoByte(Body->PlanID);
    buffer[0] = temp[0];
    buffer[1] = temp[1];
    buffer[2] = Body->SequenceID;
    temp = DivideFourByte(Body->Time);
    buffer[3] = temp[0];
    buffer[4] = temp[1];
    buffer[5] = temp[2];
    buffer[6] = temp[3];
    temp = DivideTwoByte(Body->X);
    buffer[7] = temp[0];
    buffer[8] = temp[1];
    temp = DivideTwoByte(Body->Y);
    buffer[9] = temp[0];
    buffer[10] = temp[1];
    temp = DivideTwoByte(Body->Z);
    buffer[11] = temp[0];
    buffer[12] = temp[1];
    return buffer;
}
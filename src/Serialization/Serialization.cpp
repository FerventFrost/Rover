#include "Serialization.h"

// DivideShort seperate a short into 2 bytes. eg 0x1234 -> 0x12 0x34.
// You must Delete the returned pointer after use or else memory leak will occur.
byte *Serialization::DivideTwoByte(unsigned int value)
{
    byte *bytes = new byte[2];
    bytes[0] = (value >> 8) & 0xFF;
    bytes[1] = (value)&0xFF;
    return bytes;
}

// Divide Long seperate a int into 4 bytes. eg 0x12345678 -> 0x12 0x34 0x56 0x78.
// You must Delete the returned pointer after use or else memory leak will occur.
byte *Serialization::DivideFourByte(unsigned long value)
{
    byte *bytes = new byte[4];
    bytes[0] = (value >> 24) & 0xFF;
    bytes[1] = (value >> 16) & 0xFF;
    bytes[2] = (value >> 8) & 0xFF;
    bytes[3] = (value)&0xFF;
    return bytes;
}

// Combine Int combine 2 bytes into a short. eg 0x12 0x34 -> 0x1234.
unsigned int Serialization::CombineTwoByte(byte *value)
{
    unsigned short result = 0;
    result = (result << 8) + value[0];
    result = (result << 8) + value[1];
    return result;
}

// Combine Long combine 4 bytes into a int. eg 0x12 0x34 0x56 0x78 -> 0x12345678.
unsigned long Serialization::CombineFourByte(byte *value)
{
    unsigned int result = 0;
    result = (result << 8) + value[0];
    result = (result << 8) + value[1];
    result = (result << 8) + value[2];
    result = (result << 8) + value[3];
    return result;
}

bool Serialization::isValidCRC(byte *buffer, unsigned int size, unsigned int CRC)
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

unsigned int Serialization::CalculateCRC(byte *buffer, unsigned int size)
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
byte *Serialization::SerializeHeader(StructHeader *Header)
{
    byte *buffer = new byte[(HEADER_SIZE)];
    byte *temp = new byte[2];
    buffer[0] = Header->Type;
    temp = DivideTwoByte(Header->FrameLength);
    buffer[1] = temp[0];
    buffer[2] = temp[1];
    delete[] temp;
    temp = DivideTwoByte(Header->CRC);
    buffer[3] = temp[0];
    buffer[4] = temp[1];
    delete[] temp;

    // Copy IV
    for (int i = 0; i < (16); i++)
    {
        buffer[i + 5] = Header->IV[i];
    }

    return buffer;
}

// Buffer Size is 21
StructHeader Serialization::DeserializeHeader(byte buffer[])
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

StructBody Serialization::DeserializeBodyOffline(byte buffer[])
{
    StructBody Body;
    Body.PlanID = CombineTwoByte(&buffer[0]);
    Body.SequenceID = buffer[2];
    Body.SubSystemID = buffer[3];
    Body.CommandID = buffer[4];
    Body.Delay = buffer[5];
    Body.CommandRepeat = buffer[6];
    return Body;
}

StructBody Serialization::DeserializeBodyOnline(byte buffer[])
{
    StructBody Body;
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
byte *Serialization::SerializeBodyResponse(StructBodyRequest *Request)
{
    byte *buffer = new byte[(REQUEST_SIZE)];
    buffer[0] = Request->Ack;
    buffer[1] = Request->Acktype;
    return buffer;
}

StructBodyRequest Serialization::DeserializeBodyRequest(byte buffer[])
{
    StructBodyRequest Body;
    Body.Ack = buffer[0];
    Body.Acktype = static_cast<AckType>(buffer[1]);
    return Body;
}

// Return a pointer to a buffer that contains the serialized header.
// You must Delete the returned pointer after use or else memory leak will occur.
byte *Serialization::SerializeBodyData(StructBodyData *Body)
{
    byte *buffer = new byte[(SENSOR_DATA_SIZE + 3)];
    byte *temp;
    temp = DivideTwoByte(Body->PlanID);
    buffer[0] = temp[0];
    buffer[1] = temp[1];
    delete[] temp;
    buffer[2] = Body->SequenceID;
    temp = DivideFourByte(Body->Time);
    buffer[3] = temp[0];
    buffer[4] = temp[1];
    buffer[5] = temp[2];
    buffer[6] = temp[3];
    delete[] temp;
    temp = DivideTwoByte(Body->X);
    buffer[7] = temp[0];
    buffer[8] = temp[1];
    delete[] temp;
    temp = DivideTwoByte(Body->Y);
    buffer[9] = temp[0];
    buffer[10] = temp[1];
    delete[] temp;
    temp = DivideTwoByte(Body->Z);
    buffer[11] = temp[0];
    buffer[12] = temp[1];
    buffer[13] = 0;
    buffer[14] = 0;
    buffer[15] = 0;
    delete[] temp;

    return buffer;
}

StructPlanBody Serialization::DeserializePlanBody(byte buffer[])
{
    StructPlanBody Body;
    Body.NumberofPlans = buffer[0];
    Body.NumberofFrames = buffer[1];
    Body.Time = CombineFourByte(&buffer[2]);
    return Body;
}

// Return a pointer to a buffer that contains the serialized Image Config Data that will be send by UART.
// You must Delete the returned pointer after use or else memory leak will occur.
byte *Serialization::SerializeBodyImage(StructBodyImage *body)
{
    byte *buffer = new byte[IMAGE_DATA_SIZE];
    byte *temp;
    buffer[0] = body->SequenceID;
    buffer[1] = body->OperationType;
    temp = DivideTwoByte(body->PlanID);
    buffer[2] = temp[0];
    buffer[3] = temp[1];
    delete[] temp;

    return buffer;
}

// Return a pointer to a buffer that contains the serialized Concat.
// You must Delete the returned pointer after use or else memory leak will occur.
byte *Serialization::HeaderBodyConcatenate(byte *Header, byte *Body, unsigned int BodySize)
{
    byte *buffer = new byte[(HEADER_SIZE + BodySize)];
    for (int i = 0; i < HEADER_SIZE; i++)
    {
        buffer[i] = Header[i];
    }
    for (int i = 0; i < BodySize; i++)
    {
        buffer[i + HEADER_SIZE] = Body[i];
    }

    return buffer;
}

void Serialization::printBytesAsHex(const uint8_t *bytes, size_t length)
{
    std::cout << std::hex << std::setfill('0');
    for (size_t i = 0; i < length; ++i)
    {
        std::cout << std::setw(2) << static_cast<int>(bytes[i]) << " ";
    }
    std::cout << std::dec << std::setfill(' ') << std::endl;
}
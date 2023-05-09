#ifndef Serialization_h
#define Serialization_h

#include "StructPlan.h"
#include "Arduino.h"

#define HEADER_SIZE 21
#define REQUEST_SIZE 2
#define SENSOR_DATA_SIZE 13

class Serialization
{
private:
    /* data */
public:
    static bool isValidCRC(byte *buffer, unsigned int size, unsigned int CRC);
    static unsigned int CalculateCRC(byte *buffer, unsigned int size);

    static byte *DivideTwoByte(unsigned int value);
    static byte *DivideFourByte(unsigned long value);

    static unsigned int CombineTwoByte(byte *value);
    static unsigned long CombineFourByte(byte *value);

    static byte *SerializeHeader(StructHeader *Header);
    static StructHeader DeserializeHeader(byte buffer[]);

    static StructBody DeserializeBodyOffline(byte buffer[]);
    static StructBody DeserializeBodyOnline(byte buffer[]);

    static byte *SerializeBodyResponse(StructBodyRequest *Request);
    static StructBodyRequest DeserializeBodyRequest(byte buffer[]);

    static byte *SerializeBodyData(StructBodyData *Data);

    // static void SerializeBodyImage(StructBodyImage * body, char * buffer);
};

#endif
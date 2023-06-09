#ifndef Serialization_h
#define Serialization_h

#include "StructPlan.h"
#include <Arduino.h>
#include <iomanip>
#include <iostream>

#define SENSOR_ZERO_PADDING 3
#define HEADER_SIZE 21
#define REQUEST_SIZE 2
#define SENSOR_DATA_SIZE 13
#define IMAGE_DATA_SIZE 8

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

    static StructPlanBody DeserializePlanBody(byte buffer[]);

    static byte *SerializeBodyData(StructBodyData *Data);

    static byte *HeaderBodyConcatenate(byte *Header, byte *Body, unsigned int BodySize);

    static byte *SerializeBodyImage(StructBodyImage *body);

    static void printBytesAsHex(const uint8_t *bytes, size_t length);
};

#endif
//
// Created by BAHER on 5/7/2023.
//

#ifndef TEST_CSERIALIAZATION_H
#define TEST_CSERIALIAZATION_H

#include "Struct.h"
#include <iostream>

#define HEADER_SIZE 21
#define REQUEST_SIZE 2
#define IVSize 16
#define SENSOR_DATA_SIZE 13
#define SENSOR_ZERO_PADDING 3
#define BODY_SIZE 7

class CSerialiazation
{
private:
    /* data */
public:
    static bool isValidCRC(uint8_t *buffer, uint16_t size, uint16_t CRC);
    static uint16_t CalculateCRC(uint8_t *buffer, uint16_t size);

    static uint8_t *DivideTwoByte(uint16_t value);
    static uint8_t *DivideFourByte(uint32_t value);

    static uint16_t CombineTwoByte(uint8_t *value);
    static uint32_t CombineFourByte(uint8_t *value);

    static uint8_t *SerializeHeader(StructHeader *Header);
    static StructHeader DeserializeHeader(uint8_t buffer[]);

    static StructBody DeserializeBody(uint8_t buffer[]);

    static uint8_t *SerializeBodyResponse(StructBodyRequest *Request);
    static StructBodyRequest DeserializeBodyRequest(uint8_t buffer[]);

    static uint8_t *SerializeBodyData(StructBodyData *Data);

    static uint8_t *HeaderBodyConcatenate(uint8_t *Header, uint8_t *Body, unsigned int BodySize);
};

#endif // TEST_CSERIALIAZATION_H

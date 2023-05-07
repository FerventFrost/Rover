//
// Created by BAHER on 5/7/2023.
//

#include <iostream>
#include "CSerialiazation.cpp"
#include "Struct.h"

void TestHeader()
{
    uint8_t buffer[HEADER_SIZE] = {0x00, 0x01, 0x02, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x11, 0x0C, 0x13, 0x0D, 0x0F, 0xA1, 0x11};
    StructHeader header = CSerialiazation::DeserializeHeader(buffer);
    printf("Header Type: %d\nHeader Length: %d\nHeader CRC: %d\nHeader IV: \n{", header.Type, header.FrameLength, header.CRC);
    for (int i = 0; i < IVSize; i++)
    {
        printf("%d, ", header.IV[i]);
    }
    printf("}\n");
}
int main()
{
    TestHeader();
    printf("Size of int %d", sizeof(uint32_t));
    return 0;
}
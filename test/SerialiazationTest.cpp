//
// Created by BAHER on 5/7/2023.
//

#include <iostream>
#include "CSerialiazation.cpp"
#include "Struct.h"

#include <iomanip>
#include <iostream>

void printBytesAsHex(const uint8_t *bytes, size_t length)
{
    std::cout << std::hex << std::setfill('0');
    for (size_t i = 0; i < length; ++i)
    {
        std::cout << std::setw(2) << static_cast<int>(bytes[i]) << " ";
    }
    std::cout << std::dec << std::setfill(' ') << std::endl;
}

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

void SerializeData()
{
    uint8_t *buffer = new uint8_t[(SENSOR_DATA_SIZE + SENSOR_ZERO_PADDING)];
    uint8_t *Header = new uint8_t[HEADER_SIZE];
    uint8_t *Concat = new uint8_t[(HEADER_SIZE + SENSOR_DATA_SIZE + SENSOR_ZERO_PADDING)];
    StructBodyData Data;
    Data.PlanID = 0x0A01;
    Data.SequenceID = 0x02;
    Data.Time = 0x00330A03;
    Data.X = 0x00A4;
    Data.Y = 0x00B5;
    Data.Z = 0x00C6;

    buffer = CSerialiazation::SerializeBodyData(&Data);
    for (int i = 0; i < SENSOR_ZERO_PADDING; i++)
    {
        buffer[SENSOR_DATA_SIZE + i] = 0x00;
    }

    StructHeader HeaderData;
    HeaderData.Type = FrameType::Data;
    HeaderData.FrameLength = (SENSOR_DATA_SIZE + SENSOR_ZERO_PADDING);
    HeaderData.CRC = CSerialiazation::CalculateCRC(buffer, (SENSOR_DATA_SIZE + SENSOR_ZERO_PADDING));
    for (int i = 0; i < IVSize; i++)
    {
        HeaderData.IV[i] = 0x00;
    }

    Header = CSerialiazation::SerializeHeader(&HeaderData);
    Concat = CSerialiazation::HeaderBodyConcatenate(Header, buffer, SENSOR_DATA_SIZE + SENSOR_ZERO_PADDING);

    printBytesAsHex(Concat, (HEADER_SIZE + SENSOR_DATA_SIZE + SENSOR_ZERO_PADDING));
    delete[] buffer;
    delete[] Header;
    delete[] Concat;
}

void DeserializerData()
{
    uint8_t buffer[HEADER_SIZE + SENSOR_DATA_SIZE + SENSOR_ZERO_PADDING] = {0x01, 0x02, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x11, 0x0C, 0x13, 0x0D, 0x0F, 0xA1, 0x11, 0x00, 0x01, 0x02, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x00, 0x00, 0x00};
    StructHeader header = CSerialiazation::DeserializeHeader(buffer);
    StructBody body = CSerialiazation::DeserializeBody(&buffer[HEADER_SIZE]);
    printf("Header Type: %d\nHeader Length: %d\nHeader CRC: %d\nHeader IV: \n{", header.Type, header.FrameLength, header.CRC);
    for (int i = 0; i < IVSize; i++)
    {
        printf("%d, ", header.IV[i]);
    }
    printf("}\n\n");
    printf("Body PlanID: %d\nBody SequenceID: %d\nBody SubSystemID: %d\nBody CommandID: %d\nBody Delay: %d\nBody CommandRepeat: %d\n", body.PlanID, body.SequenceID, body.SubSystemID, body.CommandID, body.Delay, body.CommandRepeat);
}
int main()
{
    SerializeData();
    DeserializerData();
    printf("Size of int %d", sizeof(uint32_t));
    return 0;
}
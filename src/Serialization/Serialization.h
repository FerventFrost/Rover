#ifndef Serialization_h
#define Serialization_h

#include "Arduino.h"

class Serialization {
    private:
        /* data */
    public:
        Serialization();
        ~Serialization();
        // static void SerializeHeader(StructHeader * header, char * buffer);
        // static void DeserializeHeader(StructHeader * header, char * buffer);
        // static void SerializeBodyOffline(StructBodyOffline * body, char * buffer);
        // static void SerializeBodyOnline(StructBodyOnline * body, char * buffer);
        // static void DeserializeBodyRequest(StructBodyRequest * body, char * buffer);
        // static void SerializeBodyResponse(StructBodyResponse * body, char * buffer);
        // static void SerializeBodyData(StructBodyData * body, char * buffer);
        // static void SerializeBodyImage(StructBodyImage * body, char * buffer);

        static bool isValidCRC(char * buffer, int size, int CRC);
        static unsigned int CRC(char * buffer, int size);
        // DivideShort seperate a short into 2 bytes. eg 0x1234 -> 0x12 0x34
        // DivideInt seperate a int into 4 bytes. eg 0x12345678 -> 0x12 0x34 0x56 0x78
        // You must Delete the returned pointer after use or else memory leak will occur
        static byte* DivideShort(unsigned short value);
        static byte* DivideInt(unsigned int value);

        // CombineShort combine 2 bytes into a short. eg 0x12 0x34 -> 0x1234
        // CombineInt combine 4 bytes into a int. eg 0x12 0x34 0x56 0x78 -> 0x12345678
        static unsigned short CombineShort(byte * value);
        static unsigned int CombineInt(byte * value);
};

#endif
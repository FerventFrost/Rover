#include "Serialization.h"

byte* Serialization::DivideShort(unsigned short value) {
    byte * bytes = new byte[2];
    bytes[0] = (byte)(value >> 8);
    bytes[1] = (byte)(value);
    return bytes;
}

byte* Serialization::DivideInt(unsigned int value) {
    byte* bytes = new byte[4];
    bytes[0] = (byte)(value >> 24);
    bytes[1] = (byte)(value >> 16);
    bytes[2] = (byte)(value >> 8);
    bytes[3] = (byte)(value);
    return bytes;
}

unsigned short Serialization::CombineShort(byte * value) {
    unsigned short result = 0;
    result = (result << 8) + value[0];
    result = (result << 8) + value[1];
    return result;
}

unsigned int Serialization::CombineInt(byte * value) {
    unsigned int result = 0;
    result = (result << 8) + value[0];
    result = (result << 8) + value[1];
    result = (result << 8) + value[2];
    result = (result << 8) + value[3];
    return result;
}


bool Serialization::isValidCRC(char * buffer, int size, int CRC) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += buffer[i];
    }
    if (sum == CRC)
        return true;
    return false;
}

unsigned int Serialization::CRC(char * buffer, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += buffer[i];
    }
    return sum;
}
#include "ESPFlash.h"

int32_t ESPFlash::ReadAddress;
int32_t ESPFlash::WriteAddress;
StructBody ESPFlash::Command;

void ESPFlash::SetupFlash()
{
    EEPROM.begin(EEPROM_SIZE);
}

StructBody ESPFlash::RetriveCommands()
{
    EEPROM.get(ReadAddress, Command);
    ReadAddress += sizeof(Command);

    return Command;
}

void ESPFlash::WriteCommand(StructBody command)
{
    EEPROM.put(WriteAddress, command);
    WriteAddress += sizeof(command);
    EEPROM.commit();
}

void ESPFlash::SetReadAddress(int32_t Address)
{
    ReadAddress = Address;
}

void ESPFlash::SetWriteAddress(int32_t Address)
{
    WriteAddress = Address;
}

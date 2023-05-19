#ifndef ESP_FLASH_H
#define ESP_FLASH_H

#include "StructPlan.h"
#include <Arduino.h>
#include <EEPROM.h>

#define EEPROM_SIZE 2500

class ESPFlash
{
private:
    static int32_t ReadAddress;
    static int32_t WriteAddress;
    static StructBody Command;

public:
    ESPFlash();
    ~ESPFlash();

    static void SetupFlash();
    static StructBody RetriveCommands();
    static void WriteCommand(StructBody command);
    static void SetReadAddress(int32_t Address);
    static void SetWriteAddress(int32_t Address);
};

#endif
#ifndef SD_CARD_H
#define SD_CARD_H

#include "Arduino.h"
#include "SD.h"
#include "FS.h"
#include "SPI.h"

#define MAX_SIZE 15
class SDCard
{
private:
    static fs::File File;

public:
    SDCard();
    ~SDCard();
    
    static bool isFileExist(fs::FS &fs, const char *path);
    
    static void MakeDirectory(fs::FS &fs, const char *path);
    static void MakeFile(fs::FS &fs, const char *path);

    static void WriteData(fs::FS &fs, fs::File file, const char *path, byte *Body);
    static byte *ReadData(fs::FS &fs, fs::File file, const char *path);
    static bool isFileAvailable(fs::FS &fs, fs::File file, const char *path);

    static void RemoveAllData(fs::FS &fs, fs::File file, const char *path);

    static bool OpenRead(fs::FS &fs, const char *path);
    static bool OpenWrite(fs::FS &fs, const char *path);
    static bool OpenAppend(fs::FS &fs, const char *path);
    static fs::File GetFile();
    static void CloseFile(fs::File File);
};

#endif
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

    // Make Directory
    static void MakeDirectory(fs::FS &fs, const char *path);
    static void MakeFile(fs::FS &fs, const char *path);

    // Read and Write Data
    static void WriteData(fs::FS &fs, fs::File file, byte *Body);
    static byte *ReadData(fs::FS &fs, fs::File file);
    static void RemoveAllData(fs::FS &fs, fs::File file);

    // Check if the File and File Data
    static bool isFileExist(fs::FS &fs, const char *path);
    static bool isDataAvailable(fs::FS &fs, fs::File file, const char *path);

    // Open and Close File
    static fs::File GetFile();
    static bool OpenRead(fs::FS &fs, const char *path);
    static bool OpenWrite(fs::FS &fs, const char *path);
    static bool OpenAppend(fs::FS &fs, const char *path);
    static void CloseFile(fs::File File);
};

#endif
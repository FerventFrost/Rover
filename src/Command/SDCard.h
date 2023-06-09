#ifndef SD_CARD_H
#define SD_CARD_H

#include "Arduino.h"
#include "SD.h"
#include "FS.h"
#include "SPI.h"

class SDCard
{
private:
    static fs::File File;

public:

    // Make Directory
    static void MakeDirectory(fs::FS &fs, const char *path);
    static void MakeFile(fs::FS &fs, const char *path);

    // Read and Write Data
    static void WriteDataln(fs::File file, byte *Body);
    static byte *ReadDataln(fs::File file);
    static void RemoveFileData(const char *path);

    // Check if the File and File Data
    static bool isFileExist(fs::FS &fs, const char *path);
    static bool isDataAvailable(fs::File file);

    // Open and Close File
    static fs::File GetFile();
    static bool OpenRead(fs::FS &fs, const char *path);
    static bool OpenWrite(fs::FS &fs, const char *path);
    static bool OpenAppend(fs::FS &fs, const char *path);
    static void CloseFile(fs::File File);
};

#endif
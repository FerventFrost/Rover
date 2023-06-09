#include "SDCard.h"
#include "SDCard.h"

fs::File SDCard::File;

bool SDCard::isFileExist(fs::FS &fs, const char *path)
{
    if (fs.exists(path))
        return true;
    return false;
}

void SDCard::MakeDirectory(fs::FS &fs, const char *path)
{
    if (!fs.exists(path))
    {
        if (fs.mkdir(path))
        {
            Serial.println("Directory created");
        }
        else
        {
            Serial.println("mkdir failed");
        }
    }
}

void SDCard::MakeFile(fs::FS &fs, const char *path)
{
    if (!fs.exists(path))
    {
        fs::File file = fs.open(path, FILE_WRITE);
        if (!file)
        {
            Serial.println("Failed to open file for writing");
        }
        else
        {
            Serial.println("File created");
        }
        file.close();
    }
}

// Note: File must be opened before calling this function and this method does not close the file
void SDCard::WriteDataln(fs::File file, byte *Body)
{
    if (!file)
        Serial.println("Failed to open file for writing");

    else
    {
        file.write(Body, sizeof(Body));
        file.write('\n');
        Serial.println("File written");
    }
}

// please delete the returned pointer after using it
// Note: File must be opened before calling this function and this method does not close the file
byte *SDCard::ReadDataln(fs::File file)
{
    if (!file)
    {
        Serial.println("Failed to open file for reading");
        file.close();
        return NULL;
    }

    byte i = 0;
    byte *Data = new byte[64];
    byte temp;

    // Read data from file until '\n' character
    while (file.available())
    {
        temp = file.read();
        if (temp == '\n')
            break;

        Data[i] = temp;
        i++;
    }
    Data[i] = '\0';
    return Data;
}

void SDCard::RemoveFileData(const char *path)
{
    fs::File file = SD.open(path, FILE_WRITE);
    if (!file)
        Serial.println("Failed to open file for writing");
    else
    {
        file.seek(0);
        file.write('\0');
        Serial.println("Data removed from the file");
    }
    file.close();
}

bool SDCard::isDataAvailable(fs::File file)
{
    if (file.available())
        return true;
    return false;
}

fs::File SDCard::GetFile()
{
    return File;
}

bool SDCard::OpenRead(fs::FS &fs, const char *path)
{
    fs::File ReadFile = fs.open(path);
    if (!ReadFile)
    {
        ReadFile.close();
        return false;
    }
    File = ReadFile;
    return true;
}

bool SDCard::OpenAppend(fs::FS &fs, const char *path)
{
    fs::File AppendFile = fs.open(path, FILE_APPEND);
    if (!AppendFile)
    {
        AppendFile.close();
        return false;
    }
    File = AppendFile;
    return true;
}

bool SDCard::OpenWrite(fs::FS &fs, const char *path)
{
    fs::File WriteFile = fs.open(path, FILE_WRITE);
    if (!WriteFile)
    {
        WriteFile.close();
        return false;
    }
    File = WriteFile;
    return true;
}

void SDCard::CloseFile(fs::File File)
{
    File.close();
}
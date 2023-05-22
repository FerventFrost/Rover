#include "SDCard.h"
#include "SDCard.h"

// Check if the File to the desired path exists
bool SDCard::isFileExist(fs::FS &fs, const char *path)
{
    if (fs.exists(path))
        return true;
    return false;
}

// Create a directory if it does not exist
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

// Create a file if it does not exist
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

// Write Data to file
// Note: File must be opened before calling this function and this method does not close the file
void SDCard::WriteData(fs::FS &fs, fs::File file, byte *Body)
{
    if (!file)
    {
        Serial.println("Failed to open file for writing");
        file.close();
    }
    else
    {
        file.write(Body, sizeof(Body));
        Serial.println("File written");
    }
}

// Read Data from file till endline character
// if file is empty or there is error close the file and return NULL
// please delete the returned pointer after using it
byte *SDCard::ReadData(fs::FS &fs, fs::File file)
{
    byte *Data = new byte[64];
    byte temp;
    byte i = 0;
    if (!file)
    {
        Serial.println("Failed to open file for reading");
        delete[] Data;
        file.close();
        return NULL;
    }
    else if (!file.available())
    {
        Serial.println("File is empty");
        delete[] Data;
        file.close();
        return NULL;
    }
    else
    {
        // Read data from file until '\n' character
        while (file.available())
        {
            temp = file.read();
            if (temp == '\n')
                break;
            else
            {
                Data[i] = temp;
                i++;
            }
        }
        Serial.println("File read");
        return Data;
    }
}

// Remove all data from file and close it
void SDCard::RemoveAllData(fs::FS &fs, fs::File file)
{

    if (!file)
    {
        Serial.println("Failed to open file for writing");
    }
    else
    {
        file.seek(0);
        file.write('\0');
        Serial.println("Data removed from the file");
    }
    file.close();
}

// Check if the file has data
bool SDCard::isDataAvailable(fs::FS &fs, fs::File file, const char *path)
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
    Serial.println("File closed");
}
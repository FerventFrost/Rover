#include "Telemetery.h"

void Telemetery::SetPath(const char *path)
{
    Path = path;
}

void Telemetery::OpenFile()
{
    if (SDCard::OpenRead(SD, Path))
    {
        File = SDCard::GetFile();
    }
}

void Telemetery::CloseFile()
{
    SDCard::CloseFile(File);
}

bool Telemetery::IsDataAvailable()
{
    return SDCard::isDataAvailable(File);
}

byte *Telemetery::GetTelemetery()
{
    if (!SDCard::isDataAvailable(File))
        return NULL;
    return SDCard::ReadDataln(File);
}

void Telemetery::RemoveData(const char *path)
{
    SDCard::RemoveFileData(path);
}
#ifndef Telemetery_H
#define Telemetery_H

#include "Serialization/Serialization.h"
#include "Command/SDCard.h"
#include "Arduino.h"

class Telemetery
{
private:
    fs::File File;
    const char *Path;

public:
    // Telemetery();
    // ~Telemetery();

    void OpenFile();
    void CloseFile();
    void SetPath(const char *path);
    void RemoveData(const char *path);

    bool IsDataAvailable();
    byte *GetTelemetery();
};
#endif
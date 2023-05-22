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
    String planAddress;

public:
    Telemetery();
    ~Telemetery();

    bool IsFileAvailable();
    byte *GetTelemetery();
    void SetPath(const char *path);
    void OpenFile();
    void CloseFile();

    // void RetriveTelemetery();
    // void SendTelemetery();
    // void DeleteTelemetery();
    // bool NextPlan();
    // bool IsPlanAvailable();
    // void RunTelemetery();
    // void SendEndOfTelemetery();
};
#endif
#ifndef Telemetery_H
#define Telemetery_H

#include "Arduino.h"

class Telemetery
{
    private:
        String planAddress;
        byte plan[];
    public:
        Telemetery();
        ~Telemetery();
        void RetriveTelemetery();
        void SendTelemetery();
        void DeleteTelemetery();
        bool NextPlan();
        bool IsPlanAvailable();
        void RunTelemetery();
        void SendEndOfTelemetery();
};
#endif
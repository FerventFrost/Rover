#ifndef AcceptPlan_H
#define AcceptPlan_H

#include "Arduino.h"

class AcceptPlan
{
    private:
        // Data
        static const byte PLAN_MAX = 5;
        byte planCounter;
        byte planID[5];
    public:
        AcceptPlan();
        void ListenPlan();
        void StorePlan();
        void AcceptInvalidPlan();
        void ExecuteAcceptPlan();
        void EndAcceptPlan();
    protected:
        bool isPlanValid();
        bool isPlanAvailable();
};

#endif 
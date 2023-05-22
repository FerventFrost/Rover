#ifndef AcceptPlan_H
#define AcceptPlan_H

#include "StructPlan.h"
#include "Serialization/Serialization.h"
#include "Command/ESPFlash.h"
#include "Arduino.h"

#define PLAN_MAX 5

class AcceptData
{
private:
    // Data
    byte PlanCounter;
    StructPlanBody *Plan;
    StructHeader Header;

public:
    AcceptData();
    ~AcceptData();
    // void ListenPlan();
    // void StorePlan();
    // void AcceptInvalidPlan();
    // void ExecuteAcceptPlan();
    // void EndAcceptPlan();

    void AcceptHeader(byte *buffer);
    bool AcceptPlan(byte *buffer);
    bool AcceptCommand(byte *buffer);
    void ResetCommandAdress();
    StructPlanBody *ReturnPlans();

protected:
    // bool isPlanValid();
    // bool isPlanAvailable();
    void SaveCommand(StructBody command);
};

#endif
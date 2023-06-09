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
    StructHeader Header;
    byte PlanCounter;
    StructPlanBody *Plan;

public:
    AcceptData();
    // ~AcceptData();

    void AcceptHeader(byte *buffer);
    bool AcceptPlan(byte *buffer);
    bool AcceptCommand(byte *buffer);

    void ResetCommandAdress();
    StructPlanBody *ReturnPlans();

protected:
    void SaveCommand(StructBody command);

};

#endif
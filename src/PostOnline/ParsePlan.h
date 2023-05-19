#ifndef PARSER_H
#define PARSER_H

#include "Offline/ExecuteOfflineCommand.h"
#include "Arduino.h"
#include "esp_timer.h"

#define MAX_PLAN_NUMBER 5

struct CallBackArgs
{
    ExecuteOfflineCommand *commandExecution;
    StructPlanBody *PlanData;
};

class PostOnline
{
private:
    /* data */
    esp_timer_handle_t PlanTimer[MAX_PLAN_NUMBER];
    esp_timer_create_args_t PlanTimerArgs;
    StructPlanBody *Plan;
    ExecuteOfflineCommand *commandExecution;

public:
    PostOnline(StructPlanBody *PlanArr, byte PlanNumber, ExecuteOfflineCommand *Execute);
    ~PostOnline();
    void CreatePlanTimer(byte PlanNumber);
    static void IRAM_ATTR PlanCallback(void *arg);
};

#endif
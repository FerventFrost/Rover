#ifndef PARSER_H
#define PARSER_H

#include "Offline/ExecuteOfflineCommand.h"
#include "Arduino.h"
#include "esp_timer.h"

#define MAX_PLAN_NUMBER 5
class PostOnline
{
private:
    /* data */
    esp_timer_handle_t PlanTimer[MAX_PLAN_NUMBER];
    esp_timer_create_args_t PlanTimerArgs;
    ExecuteOfflineCommand commandExecution;

public:
    PostOnline(ExecuteOfflineCommand Execute);
    ~PostOnline();
    void CreatePlanTimer(byte PlanNumber, unsigned long intervals[]);
    static void IRAM_ATTR PlanCallback(void *arg);
};

#endif
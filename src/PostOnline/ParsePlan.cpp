#include "ParsePlan.h"

PostOnline::PostOnline(StructPlanBody *PlanArr, byte PlanNumber, ExecuteOfflineCommand *Execute)
{
    commandExecution = Execute;
    Plan = new StructPlanBody[PlanNumber];
    for (int i = 0; i < PlanNumber; i++)
    {
        Plan[i] = PlanArr[i];
    }
}

PostOnline::~PostOnline()
{
    delete[] Plan;
}

void PostOnline::CreatePlanTimer(byte PlanNumber)
{
    char PlanTimerName[11] = "PlanTimer";

    for (int i = 0; i < PlanNumber; i++)
    {
        // Create a struct to pass the arguments to the callback function
        CallBackArgs *CallBackPlanArgs = new CallBackArgs;
        CallBackPlanArgs->commandExecution = commandExecution;
        CallBackPlanArgs->PlanData = &Plan[i];

        // Create a Name for the timer
        PlanTimerName[9] = (char)(i + 48 - 10 * (i / 10)); // convert int to char (0-9)

        // IDK if this block of code is needed to be in the loop or not
        PlanTimerArgs.callback = &PlanCallback;
        PlanTimerArgs.arg = CallBackPlanArgs;
        PlanTimerArgs.name = PlanTimerName;

        // Create the timer
        esp_timer_create(&PlanTimerArgs, &PlanTimer[i]);
    }

    // Init the timer
    for (int i = 0; i < PlanNumber; i++)
    {
        esp_timer_start_once(PlanTimer[i], (Plan[i].Time * 1000000));
    }
}

void PostOnline::PlanCallback(void *arg)
{
    Serial.println("PlanCallback");
    CallBackArgs *Args = (CallBackArgs *)arg;
    ExecuteOfflineCommand *_commandExecution = Args->commandExecution;
    _commandExecution->InitExecution(Args->PlanData);
    delete Args;
}
#ifndef Command_h
#define Command_h

#include "Sensors.h"
#include "StructPlan.cpp"
#include "Arduino.h"

class Command {
    private:
        hw_timer_s * _timer;
        uint64_t _timerValue;
    public:
        Command();
        ~Command();

        bool isTimerRunning();
        bool isCommandTurn();
        bool isCommandFinish(int * planIndex, int * planSize);
        void StartTimer();
        void SetTimerValue(uint64_t timerValue);
        void ResetTimer();

        // Read Data
        // Save Data if offline
        static void ExecuteCommand(StructPlan * plan);
        static void Sesnor(bool Online);
        static void Camera(bool Online);
        static void RoverControl(bool Online);
};

#endif
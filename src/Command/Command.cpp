#include "Command.h"

bool Command::isTimerRunning() {
    return Command::_timer != NULL;
}

// Check if this cast is valid
bool Command::isCommandTurn() {
    if( Command::_timerValue <= (int)timerReadSeconds(Command::_timer))
        return true;
    return false;
}

bool Command::isCommandFinish(int * planIndex, int * planSize) {
    if(* planIndex >= * planSize)
        return true;
    return false;
}

void Command::StartTimer() {
    Command::_timer = timerBegin(0, 80, true);
}

void Command::SetTimerValue(uint64_t timerValue) {
    Command::_timerValue = timerValue;
}

void Command::ResetTimer() {
    timerRestart(Command::_timer);
}

void Command::ExecuteCommand(StructPlan * plan) {
    if(plan->command == "Sensor") {
        Sesnor(false);
    } else if(plan->command == "Camera") {
        Camera(false);
    } else if(plan->command == "RoverControl") {
        RoverControl(false);
    }
}

void Command::Sesnor(bool Online) {
    if(Online) {
        // Send data to server
        MPU6050_Result result = Sensors::MPU_Accel();
        Serial.println(result.x);
        Serial.println(result.y);
        Serial.println(result.z);
    } else {
        // Save data to SD card
    }
}

void Command::Camera(bool Online) {
    if(Online) {
        // Send data to server
    } else {
        // Save data to SD card
    }
}

void Command::RoverControl(bool Online) {
    if(Online) {
        // Send data to server
    } else {
        // Save data to SD card
    }
}
#pragma once
#include "Application.h"

class EggTimerApp : public Application
{
public:
    void init();
    void handleInput(const uint8_t encoderValue, const bool btnPressed);
    void displayTitle();

private:
    
};
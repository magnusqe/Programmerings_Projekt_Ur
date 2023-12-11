#pragma once
#include "Application.h"

class EggTimerApp : public Application
{
public:
    void init();
    void handleInput();
    void displayTitle();

private:
    bool mRunning;

    unsigned long mTime;
    unsigned long mRemainingTime;
    unsigned long mStartTime;
};
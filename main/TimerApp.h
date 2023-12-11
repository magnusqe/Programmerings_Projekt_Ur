#pragma once
#include "Application.h"

class TimerApp : public Application
{
public:
    void init();

    void handleInput();
    void displayTitle();

private:
    void setTimer();
    void runTimer();

    void displayTime(long time);

private:
    bool mRunning;

    long mTime;
    long mRemainingTime;
    long mStartTime;
};
#pragma once
#include "Application.h"

class GuessTimeApp : public Application
{
public:
    void init();
    void handleInput();
    void displayTitle();

private:
    uint8_t mState;
    bool    mBtnhasBeenPressed;

    long    mTime;
    long    mStartTime;

    long    mTargetTime;
};
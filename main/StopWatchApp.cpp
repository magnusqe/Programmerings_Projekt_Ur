#include "StopWatchApp.h"

void StopWatchApp::init()
{
    setBackgroundColour({0, 0, 255});

    mState = 0;
    mBtnhasBeenPressed = false;

    mTime = 0;
    mStartTime = 0;
}

void StopWatchApp::handleInput()
{
    if (isButtonPressed() && !mBtnhasBeenPressed)
    {
        mState = (mState + 1) % 3;

        mBtnhasBeenPressed = true;
    }
    else if (!isButtonPressed())
    {
        mBtnhasBeenPressed = false;
    }

    long displayedTime;

    switch (mState)
    {
    case 0: // Set time to zero
        mStartTime = millis();
        displayedTime = 0;
        break;
    case 1: // Run the timer
        mTime = millis();
        displayedTime = millis() - mStartTime; 
        break;
    case 2: // Display final time
        displayedTime = mTime - mStartTime;
        break;
    }
    
    lcd->setCursor(0, 1);
    lcd->print(displayedTime / 1000);
    lcd->print(".");
    lcd->print(displayedTime / 100 % 10);
    lcd->print(displayedTime % 10);
    lcd->print("        ");
}

void StopWatchApp::displayTitle()
{
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Stopwatch!");
}
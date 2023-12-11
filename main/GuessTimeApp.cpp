#include "GuessTimeApp.h"

void GuessTimeApp::init()
{
    setBackgroundColour({0, 255, 0});
        
    mState = 0;
    mBtnhasBeenPressed = false;

    mTime = 0;
    mStartTime = 0;
    
    randomSeed(micros());
    mTargetTime = 5000 + random() % 5000;
}

void GuessTimeApp::handleInput()
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

    switch (mState)
    {
    case 0: // Show new guess
        mStartTime = millis();
        lcd->setCursor(0, 0);
        lcd->print("Target: ");

        lcd->print(mTargetTime / 1000);
        lcd->print(".");
        lcd->print(mTargetTime / 100 % 10);
        lcd->print(mTargetTime % 10);
        lcd->print("        ");

        lcd->setCursor(0, 1);
        lcd->print("0.00 s");
        break;
    case 1: // Run the hidden timer
        mTime = millis();
        lcd->setCursor(0, 1);
        lcd->print("running...");
        break;
    case 2: // Display final time
        const long finalTime = mTime - mStartTime;

        lcd->setCursor(0, 1);
        lcd->print(finalTime / 1000);
        lcd->print(".");
        lcd->print(finalTime / 100 % 10);
        lcd->print(finalTime % 10);
        lcd->print(" s       ");

        mTargetTime = 5000 + random() % 5000;
        break;
    }
}

void GuessTimeApp::displayTitle()
{
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Guess the time!");
}
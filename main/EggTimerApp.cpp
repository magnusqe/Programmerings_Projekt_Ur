#include "EggTimerApp.h"
#include "PinMacros.h"

enum EggType
{
    SoftBoiled,
    Sunny,
    HardBoiled,
    EggTypeCount
};

void EggTimerApp::init()
{
    setBackgroundColour({200, 200, 0});

    mRunning = false;
    mTime = 0;
    mRemainingTime = 0;
    mStartTime = millis();
}

void EggTimerApp::handleInput()
{
    if (!mRunning)
    {
        lcd->setCursor(0, 0);
        
        if (getEncoderValue() < 0)
        {
            write(0);
        }
        else if (getEncoderValue() >= EggTypeCount)
        {
            write(4 * (EggTypeCount - 1));
        }

        int eggType = getEncoderValue() % EggTypeCount;

        switch (eggType)
        {
        case SoftBoiled:
            mTime = 6 * 60;
            lcd->print("Soft Boiled  -->");
            break;
        case Sunny:
            mTime = 8 * 60;
            lcd->print("<--  Sunny   -->");
            break;
        case HardBoiled:
            mTime = 10 * 60;
            lcd->print("<--  Hard Boiled");
            break;
        }
        
        if (isButtonPressed())
        {
            mStartTime = millis();
            mRunning = true;
        }

        return;
    }

    const long remainingTime = mTime - (millis() - mStartTime + 1) / 1000;

    const int timeInMinutes = remainingTime / 60;
    const int timeInSeconds = remainingTime % 60;

    lcd->setCursor(0, 1);
    lcd->print("Time left: ");

    if (timeInMinutes != 0)
    {
        lcd->print(timeInMinutes);
        lcd->print("m ");
    }
    
    lcd->print(timeInSeconds);
    lcd->print("s    ");

    if (remainingTime == 0)
    {
        if (mRunning)
        {
            digitalWrite(BEEPERPIN, HIGH);
            delay(300);
            digitalWrite(BEEPERPIN, LOW);
            delay(300);
            digitalWrite(BEEPERPIN, HIGH);
            delay(500);
            digitalWrite(BEEPERPIN, LOW);
        }

        mRunning = false;
    }
}

void EggTimerApp::displayTitle()
{
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Egg Timer!");
}
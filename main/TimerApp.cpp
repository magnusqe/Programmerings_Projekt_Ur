#include "TimerApp.h"
#include "PinMacros.h"

void TimerApp::init()
{
    setBackgroundColour({200, 20, 20});

    mRunning = false;
    
    mTime = 0;
    mRemainingTime = 0;
    mStartTime = millis();
}

void TimerApp::handleInput()
{
    if (!mRunning)
    {
        setTimer();
        displayTime(mTime);
    }
    else
    {
        runTimer();
        displayTime(mRemainingTime);
    }
}

void TimerApp::setTimer()
{
    lcd->setCursor(0, 0);
    lcd->print("Set time:       ");

    if (getEncoderValue() < 0)
    {
        write(0);
    }


    mTime = (long)getEncoderValue() * 5 * 1000;
    mStartTime = millis();

    if (isButtonPressed() && getEncoderValue() != 0)
    {
        mRunning = true;
    }
}

void TimerApp::runTimer()
{
    lcd->setCursor(0, 0);
    lcd->print("The times runs!");

    mRemainingTime = mTime - (millis() - mStartTime);

    if (mRemainingTime <= 0 && mRunning)
    {
        digitalWrite(BEEPERPIN, HIGH);
        delay(300);
        digitalWrite(BEEPERPIN, LOW);
        delay(300);
        digitalWrite(BEEPERPIN, HIGH);
        delay(500);
        digitalWrite(BEEPERPIN, LOW);

        mRunning = false;
    }
}

void TimerApp::displayTime(long time)
{
    const long timeInMinutes = time / 1000 / 60;
    const long timeInSeconds = ((time + 1) / 1000) % 60;

    lcd->setCursor(1, 1);

    if (timeInMinutes != 0)
    {
        lcd->print(timeInMinutes);
        lcd->print("m ");
    }
    
    lcd->print(timeInSeconds);
    lcd->print("s    ");
}


void TimerApp::displayTitle()
{
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Timer");
}
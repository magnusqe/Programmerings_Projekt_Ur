
#include "WorldClockApp.h"

void WorldClockApp::init()
{
    setBackgroundColour({200, 20, 20});
}

void WorldClockApp::handleInput()
{
    mClock.getTime();

    lcd->setCursor(0,1);
    if (mClock.hour < 10)
        lcd->print("0");
    lcd->print(mClock.hour);
    lcd->print(":");
    if (mClock.minute < 10)
        lcd->print("0");
    lcd->print(mClock.minute);
    lcd->print(":");
    if (mClock.second < 10)
        lcd->print("0");
    lcd->print(mClock.second);
    lcd->print("    ");

    lcd->setCursor(0,0);
    if (mClock.dayOfMonth < 10)
        lcd->print("0");
    lcd->print(mClock.dayOfMonth);
    lcd->print(":");
    if (mClock.month < 10)
        lcd->print("0");
    lcd->print(mClock.month);
    lcd->print(":");
    if (mClock.year < 10)
        lcd->print("0");
    lcd->print(mClock.year);
    lcd->print(" ");

    switch (mClock.dayOfWeek)
    {
        case MON:
        lcd->print("MON");
        break;
        case TUE:
        lcd->print("TUE");
        break;
        case WED:
        lcd->print("WED");
        break;
        case THU:
        lcd->print("THU");
        break;
        case FRI:
        lcd->print("FRI");
        break;
        case SAT:
        lcd->print("SAT");
        break;
        case SUN:
        lcd->print("SUN");
        break;
    }
    lcd->print("    ");
}

void WorldClockApp::displayTitle()
{
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("World Clock");
}
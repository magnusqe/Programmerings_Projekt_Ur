#pragma once
#include "Application.h"

#include "DS1307.h"

class WorldClockApp : public Application
{
public:
    void init();
    void handleInput();
    void displayTitle();

private:
    DS1307 mClock;
};
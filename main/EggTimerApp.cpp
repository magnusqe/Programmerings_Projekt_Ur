#include "EggTimerApp.h"

void EggTimerApp::init()
{
    setBackgroundColour({200, 200, 0});
}

void EggTimerApp::handleInput(const uint8_t encoderValue, const bool btnPressed)
{
    rgb_lcd* lcd = getLCD();
}

void EggTimerApp::displayTitle()
{
    rgb_lcd* lcd = getLCD();

    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Egg Timer!");
}
#pragma once
#include <Arduino.h>
#include "rgb_lcd.h"

struct colour
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

class Application
{
public:
    Application();

    virtual void init();
    virtual void handleInput(const uint8_t encoderValue, const bool btnPressed);
    virtual void displayTitle();

public:
    colour getBackgroundColour();
    void  setBackgroundColour(const colour backgroundColour);

    rgb_lcd*  getLCD();
    void      setLCD(rgb_lcd* lcd);

private:
    colour mBackgroundColour;
    rgb_lcd* mLCD;
};
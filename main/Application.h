#pragma once
#include <Arduino.h>
#include "rgb_lcd.h"
#include "Encoder.h"

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
    virtual void handleInput();
    virtual void displayTitle();

    void setBackgroundColour(colour backgroundColour);

public:
    int getEncoderValue();
    int read();
    void write(int value);
    bool isButtonPressed();

    void printNumber(long number);

public:
    static rgb_lcd* lcd;
    static Encoder* encoder;

private:
    colour mBackgroundColour;
};
#include "Application.h"
#include "PinMacros.h"

Application::Application()
    : mBackgroundColour({255, 255, 255})
{ }

void Application::init()
{
    // Override in another file
}

void Application::handleInput()
{
    // Override in another file
}

void Application::setBackgroundColour(colour backgroundColour)
{
    mBackgroundColour = backgroundColour;
}

void Application::displayTitle()
{
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Scroll to select:");

    lcd->setRGB(mBackgroundColour.red, mBackgroundColour.green, mBackgroundColour.blue);
}

int Application::getEncoderValue()
{
    return (int)encoder->read() / 4;
}

int Application::read()
{
    return encoder->read();
}

void Application::write(int value)
{
    encoder->write(value);
}

bool Application::isButtonPressed()
{
    return (read() % 4 == 0 && !digitalRead(BUTTONPIN));
}

void Application::printNumber(long number)
{
    if (number < 10)
    {
        lcd->print("0");
    }
    lcd->print(number);
}
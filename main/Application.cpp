#include "Application.h"

Application::Application()
  : mBackgroundColour({255, 255, 0})
  , mLCD(nullptr)
{ }

void Application::init()
{
  // Override in another file
}

void Application::handleInput(const uint8_t encoderValue, const bool btnPressed)
{
  // Override in another file
}

void Application::displayTitle()
{
  mLCD->clear();
  mLCD->setCursor(0, 0);
  mLCD->print("Defualt!");
}

colour Application::getBackgroundColour()
{
  return mBackgroundColour;
}

void Application::setBackgroundColour(const colour backgroundColour)
{
  mBackgroundColour = backgroundColour;
}

rgb_lcd* Application::getLCD()
{
  return mLCD;
}

void Application::setLCD(rgb_lcd* lcd)
{
  mLCD = lcd;
}
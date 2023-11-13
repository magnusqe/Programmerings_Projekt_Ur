#include "StopWatchApp.h"

void StopWatchApp::init()
{
  setBackgroundColour({0, 0, 255});
}

void StopWatchApp::handleInput(const uint8_t encoderValue, const bool btnPressed)
{
  rgb_lcd* lcd = getLCD();

  long displayedTime;

  if (btnPressed && !mBtnhasBeenPressed)
  {
    mState = (mState + 1) % 3;

    mBtnhasBeenPressed = true;
  }
  else if (!btnPressed)
  {
    mBtnhasBeenPressed = false;
  }

  switch (mState)
  {
  case 0: // Set time to zero
    mStartTime = millis();
    displayedTime = 0;
    break;
  case 1: // Run the timer
    mTime = millis();
    displayedTime = millis() - mStartTime; 
    break;
  case 2: // Display final time
    displayedTime = mTime - mStartTime;
    break;
  }
  
  lcd->setCursor(0, 1);
  lcd->print(displayedTime / 1000);
  lcd->print(".");
  lcd->print(displayedTime / 100 % 10);
  lcd->print(displayedTime % 10);
  lcd->print("        ");
}

void StopWatchApp::displayTitle()
{
  getLCD()->clear();
  getLCD()->setCursor(0, 0);
  getLCD()->print("Stopwatch!");
}
#pragma once
#include "Application.h"

class StopWatchApp : public Application
{
public:
  void init();
  void handleInput(const uint8_t encoderValue, const bool btnPressed);
  void displayTitle();

private:
  uint8_t mState = 2;
  bool    mBtnhasBeenPressed = false;

  long    mTime = 0;
  long    mStartTime = 0;
};
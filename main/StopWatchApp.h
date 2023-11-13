#pragma once
#include "Application.h"

class StopWatchApp : public Application
{
public:
  void init();
  void handleInput(const uint8_t encoderValue, const bool btnPressed);
  void displayTitle();

private:
  void stopTheWatch();

private:
  int mState = 1;
  bool isBtnPressed = false;
};
#include "StopWatchApp.h"

void StopWatchApp::init()
{
  setBackgroundColour({0, 0, 255});
}

void StopWatchApp::handleInput(const uint8_t encoderValue, const bool btnPressed)
{
  getLCD()->setCursor(0, 1);
  getLCD()->print("Cool Beans!");
}

void StopWatchApp::displayTitle()
{
  getLCD()->clear();
  getLCD()->setCursor(0, 0);
  getLCD()->print("Stop Watch!");
}

void StopWatchApp::stopTheWatch()
{

}
#pragma once
#include "Application.h"

class ChessClockApp : public Application
{
public:
    void init();
    void handleInput();
    void displayTitle();

private:
    void selectGameMode();
    void runTimer();
    
    void switchGameState();
    void displayTime();

private:
    bool mGameModeSelection;
    bool mButtonHasBeenPressed;

    short mGameState;

    long mWhiteTime;
    long mBlackTime;
    long mIncrement;

    unsigned long mLastTime;
};
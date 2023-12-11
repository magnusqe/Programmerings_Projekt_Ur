#include "ChessClockApp.h"
#include "PinMacros.h"

enum GameType
{
    Blitz,
    Rapid,
    Classical,
    gameTypeSize
};

enum GameState
{
    WhitesTurn,
    BlacksTurn,
    HasNotStarted,
    GameOver
};

void ChessClockApp::init()
{
    setBackgroundColour({255, 0, 255});

    mGameModeSelection = true;
    mButtonHasBeenPressed = true;

    mGameState = HasNotStarted;

    mWhiteTime = 0;
    mBlackTime = 0;
    mIncrement = 0;

    mLastTime = 0;
}

void ChessClockApp::handleInput()
{
    if (mGameModeSelection)
    {
        selectGameMode();
    }
    else
    {
        runTimer();
    }
}

void ChessClockApp::runTimer()
{
    if (isButtonPressed() && !mButtonHasBeenPressed)
    {
        switchGameState();
        mButtonHasBeenPressed = true;
    }
    else if (!isButtonPressed())
    {
        mButtonHasBeenPressed = false;
    }

    lcd->setCursor(0, 0);
    switch (mGameState)
    {
    case WhitesTurn:
        mWhiteTime -= millis() - mLastTime;
        if (mWhiteTime <= 0)
        {
            lcd->clear();
            lcd->print("Black has won!");
            mGameState = GameOver;
        }
        break;
    case BlacksTurn:
        mBlackTime -= millis() - mLastTime;
        if (mBlackTime <= 0)
        {
            lcd->clear();
            lcd->print("White has won!");
            mGameState = GameOver;
        }
        break;
    default:
        break;
    }
    mLastTime = millis();
    
    if (mGameState != GameOver)
    {
        displayTime();
    }
}

void ChessClockApp::selectGameMode()
{
    if (getEncoderValue() < 0)
    {
        write(0);
    }
    else if (getEncoderValue() >= gameTypeSize)
    {
        write(4 * (gameTypeSize - 1));
    }

    lcd->setCursor(0, 0);

    unsigned int selectedGameMode = getEncoderValue() % gameTypeSize;
    switch (selectedGameMode)
    {
    case Blitz:
        lcd->print("Blitz       ");
        lcd->setCursor(0, 1);
        lcd->print("3 + 2       ");

        mBlackTime = 180000;
        mWhiteTime = 180000;
        mIncrement = 2000;

        break;
    case Rapid:
        lcd->print("Rapid       ");
        lcd->setCursor(0, 1);
        lcd->print("10 + 0      ");

        mBlackTime = 600000;
        mWhiteTime = 600000;
        mIncrement = 0;
        
        break;
    case Classical:
        lcd->print("Classical   ");
        lcd->setCursor(0, 1);
        lcd->print("30 + 15     ");

        mBlackTime = 1800000;
        mWhiteTime = 1800000;
        mIncrement = 15000;

        break;
    }

    if (isButtonPressed())
    {
        mGameModeSelection = false;
        mButtonHasBeenPressed = true;
        lcd->clear();
    }
}

void ChessClockApp::switchGameState()
{
    switch (mGameState)
    {
    case WhitesTurn:
        mWhiteTime += mIncrement;
        mGameState = BlacksTurn;
        break;
    case BlacksTurn:
        mBlackTime += mIncrement;
        mGameState = WhitesTurn;
        break;
    case HasNotStarted:
        mGameState = WhitesTurn;
        break;
    case GameOver:
        init();
        break;
    }

    digitalWrite(BEEPERPIN, HIGH);
    delay(2);
    digitalWrite(BEEPERPIN, LOW);
}

void ChessClockApp::displayTime()
{
    lcd->setCursor(0, 0);
    lcd->print("White");

    lcd->setCursor(0, 1);
    printNumber(mWhiteTime / 1000 / 60);
    lcd->print(":");    
    printNumber((mWhiteTime / 1000) % 60);

    lcd->setCursor(10, 0);
    lcd->print("Black");

    lcd->setCursor(10, 1);
    printNumber(mBlackTime / 1000 / 60);
    lcd->print(":");    
    printNumber((mBlackTime / 1000) % 60);
}

void ChessClockApp::displayTitle()
{
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Chess Clock!");
}
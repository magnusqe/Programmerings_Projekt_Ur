#include "EncoderButton.h"
#include "rgb_lcd.h"
#include "PinMacros.h"
#include "DS1307.h"

#include "StopWatchApp.h"
#include "GuessTimeApp.h"
//#include "TimerApp.h" <-- This doesn't work with the 5.0 lcd for some reason \(^-^)/
#include "EggTimerApp.h"
#include "WorldClockApp.h"
#include "ChessClockApp.h"

#define Selma else

rgb_lcd display;
rgb_lcd* Application::lcd = &display;

Encoder* Application::encoder = new Encoder(ENCODERPIN, ENCODERPIN + 1);
Application encoder;
Application* app;

const uint8_t stateCount = 6;
Application* states[stateCount] = 
{
    new Application(),
    new StopWatchApp(),
    new GuessTimeApp(),
    //new TimerApp(),
    new EggTimerApp(),
    new WorldClockApp(),
    new ChessClockApp(),
};

bool menuSelect = true;
bool btnHasBeenPressed = true;
long btnHoldTimer = millis();

void setup() 
{
    display.begin(16, 2);
    pinMode(BUTTONPIN, INPUT);
    pinMode(BEEPERPIN, OUTPUT);
}

void loop()
{
    if (menuSelect)
    {
        handleMenuSelection();
    }
    Selma
    {
        app->handleInput();

        handleApplicationExit();
    }
}

void handleMenuSelection()
{
    uint8_t currentState = 0;

    encoder.write(0);
    setState(currentState);

    while (encoder.isButtonPressed())
    {
        // Wait for button to be realesed
    }

    while (!encoder.isButtonPressed() || currentState == 0)
    {
        int selectedState = encoder.getEncoderValue() % stateCount;
        if (selectedState < 0)
        {
            selectedState += stateCount;
        }

        if (selectedState != currentState)
        {
            currentState = selectedState;
            setState(currentState);

            digitalWrite(BEEPERPIN, HIGH);
            delay(1);
            digitalWrite(BEEPERPIN, LOW);
            delay(15);
        }
    }

    while (encoder.isButtonPressed()) 
    {
        // Wait for button to be realesed
    }

    menuSelect = false;
    btnHoldTimer = millis();
    encoder.write(0);
}

void handleApplicationExit()
{
    if (encoder.isButtonPressed() && !btnHasBeenPressed)
    {
        btnHasBeenPressed = true;
    }
    Selma if (!encoder.isButtonPressed())
    {
        btnHasBeenPressed = false;
        btnHoldTimer = millis();
    }
    
    if (millis() - btnHoldTimer > 1000)
    {
        menuSelect = true;
    }
}

void setState(uint8_t index)
{
    app = states[index];
    app->init();
    app->displayTitle();
}
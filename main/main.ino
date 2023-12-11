#include "EncoderButton.h"
#include "rgb_lcd.h"
#include "PinMacros.h"
#include "DS1307.h"

#include "StopWatchApp.h"
#include "GuessTimeApp.h"
//#include "TimerApp.h"
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

int8_t currentState = -1;
int encoderValue;

void setup() 
{
    Serial.begin(9600);

    display.begin(16, 2);
    display.setCursor(0, 0);
    display.write("Hello World");

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
    encoder.write(0);

    app = states[0];
    app->init();
    app->displayTitle();

    while (encoder.isButtonPressed())
    {
        // Do nothing
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

            app = states[currentState];
            app->init();
            app->displayTitle();

            digitalWrite(BEEPERPIN, HIGH);
            delay(1);
            digitalWrite(BEEPERPIN, LOW);
            delay(15);
        }
        
        display.setRGB(app->getBackgroundColour().red, app->getBackgroundColour().green, app->getBackgroundColour().blue);
    }

    while (encoder.isButtonPressed()) 
    {
        // Do nothing
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
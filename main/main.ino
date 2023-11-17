#include "Encoder.h"
#include "rgb_lcd.h"

#include "StopWatchApp.h"
#include "GuessTimeApp.h"
#include "EggTimerApp.h"

Encoder encoder(3, 4);
rgb_lcd display;
const uint8_t buttonPin = 2;
const uint8_t beeperPin = 8;

Application* app;

const uint8_t stateCount = 4;
Application* states[stateCount] = {
    new Application(),
    new StopWatchApp(),
    new GuessTimeApp(),
    new EggTimerApp()
};

bool menuSelect = true;
long btnHoldTimer = millis();
bool btnHasBeenPressed = true;

int8_t currentState = -1;
int encoderValue;

void setup() 
{
    Serial.begin(9600);

    display.begin(16, 2);

    pinMode(buttonPin, INPUT);
    pinMode(beeperPin, OUTPUT);
}

void loop()
{
    if (menuSelect)
    {
        handleMenuSelection();

        menuSelect = false;
        btnHoldTimer = millis();
    }
    else
    {
        uint8_t encoderValue = 0;
        bool btnPressed = digitalRead(buttonPin);
        app->handleInput(encoderValue, btnPressed && !btnHasBeenPressed);

        if (btnPressed && !btnHasBeenPressed)
        {
            btnHasBeenPressed = true;
        }
        else if (!btnPressed)
        {
            btnHasBeenPressed = false;
            btnHoldTimer = millis();
        }
        
        if (millis() - btnHoldTimer > 1000)
        {
            menuSelect = true;
        }
    }
}

void handleMenuSelection()
{
    currentState = 0;
    encoder.write(0);

    app = states[currentState];
    app->setLCD(&display);

    app->init();
    app->displayTitle();

    while (digitalRead(buttonPin) != HIGH || btnHasBeenPressed || currentState == 0)
    {
        if (digitalRead(buttonPin) != HIGH)
        {    
            btnHasBeenPressed = false;
        }

        encoderValue  = (int)encoder.read() / 4;

        int selectedState = encoderValue % stateCount;
        if (selectedState < 0)
        {
            selectedState += stateCount;
        }

        if (selectedState != currentState)
        {
            currentState = selectedState;

            app = states[currentState];
            app->setLCD(&display);

            app->init();
            app->displayTitle();

            digitalWrite(beeperPin, HIGH);
        }
        else
        {
            digitalWrite(beeperPin, LOW);
        }
        
        display.setRGB(app->getBackgroundColour().red, app->getBackgroundColour().green, app->getBackgroundColour().blue);
    }

    btnHasBeenPressed = true;
}
#include "Encoder.h"
#include "rgb_lcd.h"

#include "StopWatchApp.h"

Encoder encoder(3, 4);
rgb_lcd display;
const uint8_t buttonPin = 2;
const uint8_t beeperPin = 8;

Application* app;

const uint8_t stateCount = 2;
Application* states[2] = {
  new StopWatchApp(),
  new Application()
};

bool menuSelect = true;

int8_t currentState = 0;
int encoderValue;

void setup() 
{
  Serial.begin(9600);

  display.begin(16, 2);
  display.setRGB(255, 255, 255);
  display.print("Scroll to select");

  pinMode(buttonPin, INPUT);
  pinMode(beeperPin, OUTPUT);
}

void loop()
{
  if (menuSelect)
  {
    handleMenuSelection();

    menuSelect = false;
  }
  else
  {
    uint8_t encoderValue = 0;
    bool btnPressed = digitalRead(buttonPin);

    app->handleInput(encoderValue, btnPressed);
  }
}

void handleMenuSelection()
{
  while (digitalRead(buttonPin) != HIGH)
  {
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
}
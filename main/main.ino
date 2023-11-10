#include <Encoder.h>
#include "rgb_lcd.h"

rgb_lcd lcd;
Encoder encoder(3, 4);

int encoderValue;
const int stateCount = 5;

void setup() 
{
  lcd.begin(16, 2);
  lcd.setRGB(0, 0, 0);
  lcd.print("ENCODER TEST:");
}

void loop() 
{
  encoderValue = (int)encoder.read() / 4;

  int currentState = encoderValue % stateCount;

  lcd.setCursor(0, 1);
  lcd.print(currentState);
  lcd.print(" ");
}
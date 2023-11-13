#include <Encoder.h>
#include "rgb_lcd.h"

int state = 1; //stopUp var
bool isBtnPressed; //stopUr var

const int btn = 2;
rgb_lcd lcd;
Encoder encoder(3, 4);

int encoderValue;
const int stateCount = 7;

void setup() 
{
  lcd.begin(16, 2);
  lcd.setRGB(255, 0, 0);
  lcd.print("ENCODER TEST:");
  pinMode(btn, INPUT);
}
void loop() 
{
  encoderValue = (int)encoder.read() / 4;
  int currentState = encoderValue % stateCount;
  lcd.print(currentState);
  stopUr();
}

void stopUr()
{
  int buttonState = digitalRead(btn);
  bool hasStopped;
  float time = 0; 
  float elapsedTime = millis();
  float timeStopped;
  float lastFinalTime;

  if (buttonState == HIGH && !isBtnPressed) //Acces next state on btnClick
  {
    isBtnPressed = true;
    state++;
    if (state > 3){
      state = 1;
    }
  }
  if (buttonState == LOW)
  {
    isBtnPressed = false;
  }

  if (state == 1) //Set time = 0
  {
    timeStopped = elapsedTime;
    lcd.setCursor(1,0);
    lcd.print((time)/1000);
    lcd.print("              ");
  }

  if (state == 2) //Display Running Timer
  {
    time = elapsedTime - timeStopped;
    lcd.setCursor(1,0);
    lcd.print((time)/1000);
    lcd.print("              ");

    lastFinalTime = time;
  }

  if (state == 3) //Display stopped time
  {
    lcd.setCursor(1,0);
    lcd.print(lastFinalTime/1000);
    lcd.print("              ");

  }
}

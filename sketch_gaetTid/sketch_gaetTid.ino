#include <Encoder.h>
#include "rgb_lcd.h"

int state = 1; //gaetTid var
bool isBtnPressed; //gaetTid var


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
  gaetTid();
}

void gaetTid()
{
  int buttonState = digitalRead(btn);
  const float setNumberToGuess = random(7,10);
  float numberToGuess;

  float elapsedTime = millis();
  float timeStopped;
  float finalTime;
  float score;

  if (setNumberToGuess && !numberToGuess){
    numberToGuess = setNumberToGuess;
  }
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


  if (state == 1) //Display time to guess
  {
    lcd.setCursor(0,0);
    lcd.print(numberToGuess);
    lcd.print("              ");
    lcd.setCursor(0,1);
    lcd.print("              ");


    timeStopped = elapsedTime;
  }
  if (state == 2) //Display running
  {
    lcd.setCursor(0,0);
    lcd.print("Running");
    lcd.print("              ");


    score = (finalTime/1000)-numberToGuess;
    finalTime = elapsedTime-timeStopped;
  }
  if (state == 3) //Display Score & endTime
  {
    lcd.setCursor(0,0);
    lcd.print((finalTime)/1000);
    lcd.print("              ");
    lcd.setCursor(0,1);
    lcd.print(score);
    lcd.print("              ");
  }
}
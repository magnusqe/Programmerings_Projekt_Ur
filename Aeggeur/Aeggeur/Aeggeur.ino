#include "rgb_lcd.h"
#include <Encoder.h>

rgb_lcd lcd;
Encoder encoder(3, 4);

int encoderValue;
int sekunder;
int minutter;

void setup() 
{
  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.setRGB(200, 200, 0);
  lcd.print("Aeggeur:");
}

void loop() 
{
  sekunder = encoder.read() / 4;

  if (sekunder > 59)
  {
    minutter += 1;
    sekunder = 0;
    encoder.write(0);
  }
  else
  {
    sekunder = encoder.read() / 4;
  }
  if (sekunder < 0)
  {
    minutter -= 1;
    sekunder = 59;
    encoder.write(59 * 4);
  }
  else
  {
    sekunder = encoder.read() / 4;
  }

  delay(500);
  Serial.println(minutter);
  delay(500);
  Serial.println(sekunder);

  if (buttonPressed == true)
  {
    sekunder -= 1;
    if (sekunder == 0)
    {
      buttonPressed = false;
    }
  }
}

void ClockF() 
{

    switch(Index) {
    case 0:
      SwitchScreen(EncoderFunc());
      if (ButtonFunc("Clock",0)){
        Index++;
        ClockText = "Using Cock";
        callClock = true;
      }
      break;
    case 1:

    lcd.begin(16, 3);
    //lcd.print(clock.year);
    //lcd.print(" ");
    //lcd.print(clock.month);
    //lcd.print(" ");
    //lcd.print(clock.dayOfWeek);
    //lcd.print(" ");
    lcd.print((clock.hour += clock.minute / 60));
    lcd.print(":");
    lcd.print((clock.minute += clock.second / 60));
    lcd.print(":");
    lcd.print(((clock.second = clock.second % 60) += 1)-1);

    if (ButtonFunc("Clock",0)){
      ClockText = "Cock";
      callClock = true;
      Index = 0;
    }

      break;
    default:
      break;
  }

  delay(1000);

  if(callClock == true)
  {
    int Index = 0;
    
    lcd.begin(16, 2);
    lcd.print(ClockText);
    Serial.println(state);
    callStop = true;
    callGuess = true;
    callBoil = true;
    callAlarm = true;
    callClock = false;
    colorR = 204;
    colorG = 255;
    colorB = 236;
    
    lcd.setRGB(colorR, colorG, colorB);
  }

}
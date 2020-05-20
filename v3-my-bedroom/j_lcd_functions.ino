void display_status(){
  lcd.setCursor(0, 0);
  lcd.print(F("LA: "));
  
  if (isLightAOn == 0){
    lcd.print(F("Off "));
  }
  else if (isLightAOn == 1){
    lcd.print(F("On  "));
  }
  
  lcd.setCursor(8, 0);
  lcd.print(F("LB: "));
  
  if (isLightBOn == 0){
    lcd.print(F("Off "));
  }
  else if (isLightBOn == 1){
    lcd.print(F("On  "));
  }

  lcd.setCursor(0, 1);
  lcd.print(F("Temp: "));
  
  lcd.setCursor(6, 1);
  lcd.print(temp_c);
  
  lcd.setCursor(10, 1);
  lcd.print((char)223);
  lcd.print(F("C    "));
}

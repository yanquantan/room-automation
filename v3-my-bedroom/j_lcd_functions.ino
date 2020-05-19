void display_status(){
  lcd.setCursor(0, 0);
  lcd.print("LA: ");
  
  if (isLightAOn == 0){
    lcd.print("Off ");
  }
  else if (isLightAOn == 1){
    lcd.print("On  ");
  }
  
  lcd.setCursor(8, 0);
  lcd.print("LB: ");
  
  if (isLightBOn == 0){
    lcd.print("Off ");
  }
  else if (isLightBOn == 1){
    lcd.print("On  ");
  }

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  
  lcd.setCursor(6, 1);
  lcd.print(temp_c);
  
  lcd.setCursor(10, 1);
  lcd.print((char)223);
  lcd.print("C    ");
}

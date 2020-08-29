void display_status(){
  lcd.setCursor(0, 0);
  lcd.print("L: ");
  
  if (isLightOn == 0){
    lcd.print("Off  ");
  }
  else if (isLightOn == 1){
    lcd.print("On   ");
  }
  
  lcd.setCursor(8, 0);
  lcd.print("AC: ");
  
  if (isAirconOn == 0){
    lcd.print("Off ");
  }
  else if (isAirconOn == 1){
    lcd.print("On  ");
  }

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  
  lcd.setCursor(6, 1);
  lcd.print(getCurrentTemp());
  
  lcd.setCursor(10, 1);
  lcd.print((char)223);
  lcd.print("C    ");
}

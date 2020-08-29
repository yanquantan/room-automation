#include <LiquidCrystal.h>

LiquidCrystal lcd(rs_pin, en_pin, d4_pin, d5_pin, d6_pin, d7_pin);

void setup_lcd(){
  lcd.begin(16,2);
  pinMode(anode_pin, OUTPUT);
  pinMode(cathode_pin, OUTPUT);

  digitalWrite(anode_pin, HIGH);
  digitalWrite(cathode_pin, LOW);

  lcd.setCursor(2, 0);
  // Print the string 'Hello World!':
  lcd.print("Hello World!");
}

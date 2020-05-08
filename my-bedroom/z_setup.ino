void setup(){
  EspSerial.begin(ESP8266_BAUD); // Set ESP8266 baud rate
  delay(10);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Initialising...");

  sensors.begin();

  Blynk.begin(auth, wifi, ssid, pass);

  reset_servos();

  timer.setInterval(update_period, update_server);

  pinMode(relay_pin, OUTPUT);
}

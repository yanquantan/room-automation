void setup(){
  EspSerial.begin(ESP8266_BAUD); // Set ESP8266 baud rate
  delay(10);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Initialising...");

  Blynk.begin(auth, wifi, ssid, pass);

  reset_servos();

  timer.setInterval(update_period, update_server);

  pinMode(temp_sensor_pin, INPUT);

  pinMode(light_status_pin, OUTPUT);
  pinMode(aircon_status_pin, OUTPUT);
}

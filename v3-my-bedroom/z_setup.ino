byte connectedToESP8266 = 0;
byte connectedToSerialMonitor = 0;

void setup(){
  EspSerial.begin(ESP8266_BAUD); // Set ESP8266 baud rate
  delay(10);

  Serial.println(F("Press the 'Send' button to begin configuration... (you have 5 seconds)"));
  delay(1000);
  Serial.println(F("5... "));
  delay(1000);
  Serial.println(F("4... "));
  delay(1000);
  Serial.println(F("3... "));
  delay(1000);
  Serial.println(F("2... "));
  delay(1000);
  Serial.println(F("1... "));
  delay(1000);
  Serial.println(F("Too late! Disconnect power and try again."));

  if (Serial.available() > 0) {
    String incomingStr = Serial.readString();

    if (incomingStr == "\r\n"){
      connectedToSerialMonitor = 1;
      Serial.println(F("Success! You are now configuring the WiFi settings."));
    }
    else{
      connectedToESP8266 = 1;
    }
  }
  else{
    connectedToESP8266 = 1;
  }

  if (connectedToESP8266 == 1){
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print(F("Initialising..."));
  
    sensors.begin();
  
    Blynk.begin(auth, wifi, ssid, pass);
  
    reset_servos();
  
    timer.setInterval(update_period, update_server);
  
    pinMode(relay_pin, OUTPUT);
  }

  if (connectedToSerialMonitor == 1){
    //do something
  }
}

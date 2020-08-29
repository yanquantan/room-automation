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
  
  if (Serial.available() > 0) {
    String incomingStr = Serial.readString();

    if (incomingStr == "\r\n"){
      connectedToSerialMonitor = 1;
      Serial.println(F("Success! You are now configuring the WiFi settings."));
    }
    else{
      Serial.println(F("Too late! Disconnect power and try again."));
      connectedToESP8266 = 1;
    }
  }
  else{
    Serial.println(F("Too late! Disconnect power and try again."));
    connectedToESP8266 = 1;
  }

  if (connectedToESP8266 == 1){
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print(F("Initialising..."));
  
    sensors.begin();
  
    Blynk.begin(readStringFromEEPROM(100).c_str(), wifi, readStringFromEEPROM(200).c_str(), readStringFromEEPROM(300).c_str());
  
    reset_servos();
  
    timer.setInterval(update_period, update_server);
  }

  if (connectedToSerialMonitor == 1){
    String incomingStr;
    
    Serial.println(F("Paste your Auth Token and press 'Send'!"));

    while(!Serial.available() ){
      // do nothing
    }
  
    if (Serial.available() > 0) {
      incomingStr = Serial.readString();
    }
  
    writeStringToEEPROM(100, incomingStr);

    Serial.print(F("Your Auth Token is: "));
    Serial.println(readStringFromEEPROM(100));

    Serial.println(F("Paste your WiFi SSID and press 'Send'!"));

    while(!Serial.available() ){
      // do nothing
    }
  
    if (Serial.available() > 0) {
      incomingStr = Serial.readString();
    }
  
    writeStringToEEPROM(200, incomingStr);

    Serial.print(F("Your WiFi SSID is: "));
    Serial.println(readStringFromEEPROM(200));

    Serial.println(F("Paste your WiFi Password and press 'Send'!"));

    while(!Serial.available() ){
      // do nothing
    }
  
    if (Serial.available() > 0) {
      incomingStr = Serial.readString();
    }
  
    writeStringToEEPROM(300, incomingStr);

    Serial.print(F("Your WiFi Password is: "));
    Serial.println(readStringFromEEPROM(300));

    Serial.println(F("You have successfully configured the WiFi settings."));
  }
}

int connectedToESP8266 = 0;
int connectedToSerialMonitor = 0;
String incomingStr;

void setup(){
  EspSerial.begin(ESP8266_BAUD); // Set ESP8266 baud rate

  Serial.println("Press the 'Send' button to begin configuration... (you have 5 seconds)");
  Serial.println();
  delay(5000);

  if (Serial.available() > 0) {
    incomingStr = Serial.readString();
    
    if (incomingStr == "\r\n"){
      connectedToSerialMonitor = 1;
      Serial.println("Success! You are now configuring the WiFi settings.");
      Serial.println();
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
    lcd.print("Initialising...");
  
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

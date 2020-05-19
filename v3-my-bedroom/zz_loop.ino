void loop(){
  if (connectedToESP8266 == 1){
    Blynk.run();
    timer.run();
  
    display_status();
  }
}

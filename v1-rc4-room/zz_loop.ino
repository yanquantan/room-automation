void loop(){
  Blynk.run();
  timer.run();

  display_status();

  digitalWrite(light_status_pin, isLightOn);
  digitalWrite(aircon_status_pin, isAirconOn);
}

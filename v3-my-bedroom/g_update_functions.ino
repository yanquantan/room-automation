void update_server(){
  update_switch_status();
  update_temperature_status();
}

void update_switch_status(){
  Blynk.virtualWrite(V0, isLightAOn);
  Blynk.virtualWrite(V1, isLightBOn);
}

void update_temperature_status(){
  update_temp();
}

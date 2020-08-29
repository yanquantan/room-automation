void update_temp(){
  Blynk.virtualWrite(V4, getCurrentTemp());
}

void update_switch_status(){
  Blynk.virtualWrite(V0, isLightOn*255);
  Blynk.virtualWrite(V1, isAirconOn*255);
}

void update_server(){
  update_switch_status();
  update_temp();
}

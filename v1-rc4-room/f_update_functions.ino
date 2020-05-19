void update_server(){
  update_switch_status();
  update_temperature_status();
}

void update_switch_status(){
  Blynk.virtualWrite(V0, isLightOn*255);
  Blynk.virtualWrite(V1, isAirconOn*255);
}

void update_temperature_status(){
  change_aRef_to_1p1();
  timer.setTimeout(100, update_temp);
  timer.setTimeout(200, change_aRef_to_5p0);
}

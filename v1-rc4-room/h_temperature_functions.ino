void change_aRef_to_1p1(){
  aRef_value = 0.0; //transition value

  analogReference(INTERNAL);
  analogRead(temp_sensor_pin);
  timer.setTimeout(100, update_aRef_1p1);
}

void change_aRef_to_5p0(){
  aRef_value = 0.0; //transition value

  analogReference(DEFAULT);
  analogRead(temp_sensor_pin);
  timer.setTimeout(100, update_aRef_5p0);
}

void update_aRef_1p1(){
  aRef_value = 1.1;
}

void update_aRef_5p0(){
  aRef_value = 5.0;
}

void update_temp(){
  temp_vout = analogRead(temp_sensor_pin);
  temp_c = (temp_vout*110)/1023;

  Blynk.virtualWrite(V2, temp_c);
}

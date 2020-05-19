void update_temp(){
  sensors.requestTemperatures();
  temp_c = sensors.getTempCByIndex(0);

  Blynk.virtualWrite(V2, temp_c);
}

float getCurrentTemp(){
  ds18b20.requestTemperatures();
  float tempC = ds18b20.getTempCByIndex(0);

  return tempC;
}

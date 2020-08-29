void callback(char* topic, byte *payload, unsigned int length) {
    Serial.println("-------new message from broker-----");
    Serial.print("channel:");
    Serial.println(topic);
    Serial.print("data:");  
    Serial.write(payload, length);
    Serial.println();
}

void publishTempData(float tempC){
  if (!client.connected()) {
    reconnect();
  }

  char tempString[6];
  snprintf(tempString, sizeof tempString, "%f", tempC);

  //Serial.print("temp sent:");
  //Serial.println(tempString);

  char sendString[40];
  strcpy(sendString, "{\"data\":");
  strcat(sendString, tempString);
  strcat(sendString, ", \"write\":true}");

  //Serial.print("string sent:");
  //Serial.println(sendString);

  client.publish(MQTT_TEMP_CH, sendString);
}

void mqtt_loop(){
  client.loop();
}

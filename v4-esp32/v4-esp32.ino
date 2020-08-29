#include "a_pin_usage.h"
#include "b_wifi_config.h"
#include "c_mqtt_config.h"
#include "d_temp_config.h"
#include "e_lcd_config.h"
#include "f_servo_config.h"
#include "g_temp_functions.h"
#include "z_mqtt_functions.h"

unsigned long previousMillis = 0;
const long send_temp_interval = 60000; 

void setup(){
  Serial.begin(115200);
  setup_lcd();
  setup_temp();
  setup_wifi();
  setup_mqtt();
  setup_servo();
}
  
void loop(){
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= send_temp_interval){
    previousMillis = currentMillis;

    float tempC = getCurrentTemp();
    publishTempData(tempC);
  }

  mqtt_loop();
}

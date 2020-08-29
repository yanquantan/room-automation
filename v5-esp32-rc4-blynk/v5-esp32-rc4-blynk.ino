#include "a_pin_usage.h"
#include "b_blynk_config.h"
#include "c_temp_config.h"
#include "d_lcd_config.h"
#include "e_servo_config.h"
#include "f_temp_functions.h"
#include "g_lcd_functions.h"
#include "h_servo_functions.h"
#include "i_update_functions.h"

void setup(){
  Serial.begin(115200);

  setup_blynk();
  setup_temp();
  setup_lcd();
  setup_servo();

  timer.setInterval(update_period, update_server);
}
  
void loop(){
  Blynk.run();
  timer.run();

  display_status();
}

BLYNK_CONNECTED(){
    Blynk.syncVirtual(V0, V1);
}

BLYNK_WRITE(V0){
  isLightOn = param.asInt()/255;
}

BLYNK_WRITE(V1){
  isAirconOn = param.asInt()/255;
}

BLYNK_WRITE(V2){
  if(param.asInt() == 1){
    switch_on_lights();
  }

  else if(param.asInt() == 0){
    switch_off_lights();
  }
}

BLYNK_WRITE(V3){
  if(param.asInt() == 1 && isAirconOn == 0){
    switch_on_aircon();
  }

  else if(param.asInt() == 0 && isAirconOn == 1){
    switch_off_aircon();
  }
}

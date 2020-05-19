#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <Servo.h>
#include <LiquidCrystal.h>
#include <OneWire.h> 
#include <DallasTemperature.h>

#include "a_pin_usage.h"
#include "b_wifi_config.h" // remember to change this file
#include "c_lcd_config.h"
#include "d_temperature_config.h"
#include "e_global_variables.h"
#include "f_function_prototypes.h"

/*
 * Blink Commands Below
 * Note: These commands can't be moved to another tab due to Blynk constraints
 */

BLYNK_CONNECTED(){
    Blynk.syncVirtual(V0, V1);
}

BLYNK_WRITE(V0){
  isLightAOn = param.asInt();
}

BLYNK_WRITE(V1){
  isLightBOn = param.asInt();
}

BLYNK_WRITE(V9){
  if(param.asInt() == 1){
    switch_on_light_A();
  }

  else if(param.asInt() == 0){
    switch_off_light_A();
  }
}

BLYNK_WRITE(V11){
  if(param.asInt() == 1){
    switch_on_light_B();
  }

  else if(param.asInt() == 0){
    switch_off_light_B();
  }
}

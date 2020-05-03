BlynkTimer timer;
long update_period = 10000L; // server is updated every 10s

float temp_c;
float temp_vout;
float aRef_value = 5.0; // Normal: 5.0, Temperature Reading: 1.1, Transition: 0.0

Servo lightOn_servo, lightOff_servo, aircon_servo;
long servo_reset_time = 2000L;
long servo_detach_time = 1000L;

int isLightOn, isAirconOn;

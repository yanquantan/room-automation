BlynkTimer timer;
long update_period = 10000L; // server is updated every 10s

float temp_c;
float temp_vout;
float aRef_value = 5.0; // Normal: 5.0, Temperature Reading: 1.1, Transition: 0.0

Servo lightAOn_servo, lightBOn_servo, lightAOff_servo, lightBOff_servo;
int servo_reset_time = 2000;
int servo_detach_time = 1000;

byte isLightAOn, isLightBOn;

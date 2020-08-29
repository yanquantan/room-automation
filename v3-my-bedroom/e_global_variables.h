BlynkTimer timer;
long update_period = 10000L; // server is updated every 10s

float temp_c;

Servo lightAOn_servo, lightBOn_servo, lightAOff_servo, lightBOff_servo;
int servo_reset_time = 2000;
int servo_detach_time = 1000;

byte isLightAOn, isLightBOn;

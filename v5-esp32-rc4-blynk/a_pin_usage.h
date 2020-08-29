#define temp_sensor_pin 32

#define rs_pin 22
#define en_pin 23
#define d4_pin 21
#define d5_pin 19
#define d6_pin 18
#define d7_pin 5
#define anode_pin 17
#define cathode_pin 16

#define lightOn_servo_pin 4
#define lightOff_servo_pin 13
#define aircon_servo_pin 12

long update_period = 10000L; // server is updated every 10s
int isLightOn, isAirconOn;
long servo_reset_time = 2000L;
long servo_detach_time = 1000L;

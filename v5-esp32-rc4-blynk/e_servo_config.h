#include <Servo.h>

Servo lightOn_servo;
Servo lightOff_servo;
Servo aircon_servo;

void attach_servos(){
  lightOn_servo.attach(lightOn_servo_pin);
  lightOff_servo.attach(lightOff_servo_pin);
  aircon_servo.attach(aircon_servo_pin);
}

void detach_servos(){
  lightOn_servo.detach();
  lightOff_servo.detach();
  aircon_servo.detach();
}

void reset_servos(){
  attach_servos();

  lightOn_servo.write(0);
  lightOff_servo.write(180);
  aircon_servo.write(180);

  timer.setTimeout(servo_detach_time, detach_servos);
}

void setup_servo(){
  reset_servos();
}

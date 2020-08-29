#include <Servo.h>

Servo lightOnServo;
Servo lightOffServo;

void setup_servo(){
  lightOffServo.attach(4);
  lightOnServo.attach(13);
}

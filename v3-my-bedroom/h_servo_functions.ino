void switch_on_light_A(){
  lightAOn_servo.attach(lightAOn_servo_pin);
  lightAOn_servo.write(0);
  timer.setTimeout(servo_detach_time, detach_servos);

  isLightAOn = 1;
  Blynk.virtualWrite(V0, isLightAOn);
  timer.setTimeout(servo_reset_time, reset_servos);
};

void switch_off_light_A(){
  lightAOff_servo.attach(lightAOff_servo_pin);
  lightAOff_servo.write(180);
  timer.setTimeout(servo_detach_time, detach_servos);

  isLightAOn = 0;
  Blynk.virtualWrite(V0, isLightAOn);
  timer.setTimeout(servo_reset_time, reset_servos);
};

void switch_on_light_B(){
  lightBOn_servo.attach(lightBOn_servo_pin);
  lightBOn_servo.write(180);
  timer.setTimeout(servo_detach_time, detach_servos);

  isLightBOn = 1;
  Blynk.virtualWrite(V1, isLightBOn);
  timer.setTimeout(servo_reset_time, reset_servos);
};

void switch_off_light_B(){
  lightBOff_servo.attach(lightBOff_servo_pin);
  lightBOff_servo.write(0);
  timer.setTimeout(servo_detach_time, detach_servos);

  isLightBOn = 0;
  Blynk.virtualWrite(V1, isLightBOn);
  timer.setTimeout(servo_reset_time, reset_servos);
};

void reset_servos(){
  attach_servos();

  lightAOn_servo.write(180);
  lightBOn_servo.write(0);
  lightAOff_servo.write(0);
  lightBOff_servo.write(180);

  timer.setTimeout(servo_detach_time, detach_servos);
}

void attach_servos(){
  lightAOn_servo.attach(lightAOn_servo_pin);
  lightBOn_servo.attach(lightBOn_servo_pin);
  lightAOff_servo.attach(lightAOff_servo_pin);
  lightBOff_servo.attach(lightBOff_servo_pin);
}

void detach_servos(){
  lightAOn_servo.detach();
  lightBOn_servo.detach();
  lightAOff_servo.detach();
  lightBOff_servo.detach();
}

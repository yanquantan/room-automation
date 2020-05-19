void switch_on_lights(){
  lightOn_servo.attach(lightOn_servo_pin);
  lightOn_servo.write(180);
  timer.setTimeout(servo_detach_time, detach_servos);

  isLightOn = 1;
  Blynk.virtualWrite(V0, isLightOn*255);
  timer.setTimeout(servo_reset_time, reset_servos);
};

void switch_off_lights(){
  lightOff_servo.attach(lightOff_servo_pin);
  lightOff_servo.write(0);
  timer.setTimeout(servo_detach_time, detach_servos);

  isLightOn = 0;
  Blynk.virtualWrite(V0, isLightOn*255);
  timer.setTimeout(servo_reset_time, reset_servos);
};

void switch_on_aircon(){
  aircon_servo.attach(aircon_servo_pin);
  aircon_servo.write(180);
  timer.setTimeout(servo_detach_time, detach_servos);

  isAirconOn = 1;
  Blynk.virtualWrite(V1, isAirconOn*255);
  timer.setTimeout(servo_reset_time, reset_servos);
};

void switch_off_aircon(){
  aircon_servo.attach(aircon_servo_pin);
  aircon_servo.write(180);
  timer.setTimeout(servo_detach_time, detach_servos);

  isAirconOn = 0;
  Blynk.virtualWrite(V1, isAirconOn*255);
  timer.setTimeout(servo_reset_time, reset_servos);
};

void reset_servos(){
  attach_servos();

  lightOn_servo.write(0);
  lightOff_servo.write(180);
  aircon_servo.write(0);

  timer.setTimeout(servo_detach_time, detach_servos);
}

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

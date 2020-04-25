#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <Servo.h>
//#include <LiquidCrystal.h>

#include "header.h" // imports auth, ssid and pass stored in header.h

// PIN USAGE
// =============
// D2: isLightOn (Trigger)
// D3: isAirconOn (Echo)
// D4 to D10: (LCD Display)
// D11: (PIR Sensor)
// D12: WiFi RX
// D13: WiFi TX
// -------------
// A0: LCD Shield Buttons
// A1: Temperature Sensor
// A2: (LDR?)
// A3: Light On Servo
// A4: Light Off Servo
// A5: Aircon Toggle Servo
// -------------
// V0: isLightOn
// V1: isAirconOn
// V2: Temperature Reading
// V9: Light Control (from app / Google Assistant)
// V11: Aircon Control (from app / Google Assistant)

//////////////////// WiFi Shield Setup ////////////////////
extern const char auth[];
extern const char ssid[];
extern const char pass[];

#include <SoftwareSerial.h>
SoftwareSerial EspSerial(12, 13); // RX, TX

#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);

//////////////////// Pin Definitions ////////////////////
const int light_status_pin = 2;
const int aircon_status_pin = 3;

const int temp_input_pin = A1;
float temp_c;
float temp_vout;

BlynkTimer timer;
void update_server();
long update_period = 10000L; // server is updated every 10s

void update_temp();
void reset_aRef();
float aRef_value = 5.0;

Servo lightOn_servo, lightOff_servo, aircon_servo;
void reset_servos();
void detach_servos();
long servo_reset_time = 5000L;
long servo_detach_time = 2000L;

int isLightOn, isAirconOn;

//////////////////// Things to do when Blynk virtual pins are updated ////////////////////
BLYNK_CONNECTED(){
    Blynk.syncVirtual(V0, V1);
}

BLYNK_WRITE(V0){
  isLightOn = param.asInt()/255;
}

BLYNK_WRITE(V1){
  isAirconOn = param.asInt()/255;
}

BLYNK_WRITE(V9){
  if(param.asInt() == 1){
    lightOn_servo.attach(A3);
    lightOn_servo.write(180);
    timer.setTimeout(servo_detach_time, detach_servos);
    
    isLightOn = 1;
    Blynk.virtualWrite(V0, isLightOn*255);
    timer.setTimeout(servo_reset_time, reset_servos);
  }
  
  else if(param.asInt() == 0){
    lightOff_servo.attach(A4);
    lightOff_servo.write(0);
    timer.setTimeout(servo_detach_time, detach_servos);
    
    isLightOn = 0;
    Blynk.virtualWrite(V0, isLightOn*255);
    timer.setTimeout(servo_reset_time, reset_servos);
  }
}

BLYNK_WRITE(V11){
  if(param.asInt() == 1 && isAirconOn == 0){
    aircon_servo.attach(A5);
    aircon_servo.write(180);
    timer.setTimeout(servo_detach_time, detach_servos);
    
    isAirconOn = 1;
    Blynk.virtualWrite(V1, isAirconOn*255);
    timer.setTimeout(servo_reset_time, reset_servos);
  }
  
  else if(param.asInt() == 0 && isAirconOn == 1){
    aircon_servo.attach(A5);
    aircon_servo.write(180);
    timer.setTimeout(servo_detach_time, detach_servos);
    
    isAirconOn = 0;
    Blynk.virtualWrite(V1, isAirconOn*255);
    timer.setTimeout(servo_reset_time, reset_servos);
  } 
}

//////////////////// Functions Called by Timer Definitions ////////////////////
void update_server(){
  aRef_value = 0.0;
  analogReference(INTERNAL);
  analogRead(temp_input_pin);

  timer.setTimeout(100, update_temp);
}

void update_temp(){
  aRef_value = 1.1;
  
  temp_vout = analogRead(temp_input_pin);
  temp_c = (temp_vout*110)/1023;
  
  Blynk.virtualWrite(V0, isLightOn*255);
  Blynk.virtualWrite(V1, isAirconOn*255);
  Blynk.virtualWrite(V2, temp_c);

  aRef_value = 0.0;
  analogReference(DEFAULT);
  analogRead(temp_input_pin);

  timer.setTimeout(100, reset_aRef);
}

void reset_aRef(){
  aRef_value = 5.0;
}

void reset_servos(){
  lightOn_servo.attach(A3);
  lightOff_servo.attach(A4);
  aircon_servo.attach(A5);
  
  lightOn_servo.write(0);
  lightOff_servo.write(180);
  aircon_servo.write(0);

  timer.setTimeout(servo_detach_time, detach_servos);
}

void detach_servos(){
  lightOn_servo.detach();
  lightOff_servo.detach();
  aircon_servo.detach();
}

//////////////////// Arduino Setup and Loop ////////////////////
void setup(){
  EspSerial.begin(ESP8266_BAUD); // Set ESP8266 baud rate
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);

  reset_servos();

  timer.setInterval(update_period, update_server);

  pinMode(temp_input_pin, INPUT);

  pinMode(light_status_pin, OUTPUT);
  pinMode(aircon_status_pin, OUTPUT);
}

void loop(){
  Blynk.run();
  timer.run();

  digitalWrite(light_status_pin, isLightOn);
  digitalWrite(aircon_status_pin, isAirconOn);
}

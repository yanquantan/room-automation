#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <Servo.h>
//#include <LiquidCrystal.h>

#include "header.h" // imports auth, ssid and pass stored in header.h

// PIN USAGE
// =============
// D2: isLightOn
// D3: isAirconOn
// D4 to D10: LCD Display
// D12: WiFi RX
// D13: WiFi TX
// -------------
// A0: LCD Shield Buttons
// A1: Temperature Sensor
// A3: Servo 9 (Light On)
// A4: Servo 10 (Light Off)
// A5: Servo 11 (Aircon Toggle)
// -------------
// V0: isLightOn
// V1: isAirconOn
// V2: Temperature Reading
// V9: Light Control (from app / Google Assistant)
// V11: Aircon Control (from app / Google Assistant)

extern const char auth[];
extern const char ssid[];
extern const char pass[];

#include <SoftwareSerial.h>
SoftwareSerial EspSerial(12, 13); // RX, TX

#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);

const int light_status_pin = 2;
const int aircon_status_pin = 3;

const int temp_input_pin = A1;
float temp_c;
float temp_vout;

BlynkTimer update_timer; //used for pushing values to Blynk server
void update_server();
long update_period = 10000L; // server is updated every 60s

void update_temp();
float aRef_value = 5.0;

Servo servo9, servo10, servo11; // 9: Light on, 10: Light off, 11: Aircon Switch
BlynkTimer servo_reset_timer;
void reset_servos();
long servo_reset_time = 5000L;

int isLightOn, isAirconOn;

/////////////////////////Things to do when Blynk virtual pins are updated
BLYNK_CONNECTED() {
    Blynk.syncVirtual(V0, V1);
}

BLYNK_WRITE(V0)
{
  isLightOn = param.asInt()/255;
}

BLYNK_WRITE(V1)
{
  isAirconOn = param.asInt()/255;
}

BLYNK_WRITE(V9)
{
  if(param.asInt() == 1){
    servo9.write(180);
    isLightOn = 1;
    Blynk.virtualWrite(V0, isLightOn*255);
    servo_reset_timer.setTimeout(servo_reset_time, reset_servos);
  }
  
  else if(param.asInt() == 0){
    servo10.write(180);
    isLightOn = 0;
    Blynk.virtualWrite(V0, isLightOn*255);
    servo_reset_timer.setTimeout(servo_reset_time, reset_servos);
  }
}

BLYNK_WRITE(V11)
{
  if(param.asInt() == 1 && isAirconOn == 0){
    servo11.write(180);
    isAirconOn = 1;
    Blynk.virtualWrite(V1, isAirconOn*255);
    servo_reset_timer.setTimeout(servo_reset_time, reset_servos);
  }
  
  else if(param.asInt() == 0 && isAirconOn == 1){
    servo11.write(180);
    isAirconOn = 0;
    Blynk.virtualWrite(V1, isAirconOn*255);
    servo_reset_timer.setTimeout(servo_reset_time, reset_servos);
  } 
}

////////////////////////Functions Called by Timer Definitions
void update_server(){
  analogReference(INTERNAL);
  aRef_value = 1.1;
  analogRead(temp_input_pin);

  servo_reset_timer.setTimeout(100, update_temp); // using servo_reset_timer to save memory - CHANGE NAME OF TIMER
}

void update_temp(){
  temp_vout = analogRead(temp_input_pin);
  temp_c = (temp_vout*110)/1023;
  
  Blynk.virtualWrite(V0, isLightOn*255);
  Blynk.virtualWrite(V1, isAirconOn*255);
  Blynk.virtualWrite(V2, temp_c);

  analogReference(DEFAULT);
  aRef_value = 5.0;
  analogRead(temp_input_pin);
}

void reset_servos(){
  servo9.write(0);
  servo10.write(0);
  servo11.write(0);
}

////////////////////////Arduino Setup and Loop
void setup()
{
  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);

  servo9.attach(A3);
  servo10.attach(A4);
  servo11.attach(A5);
  reset_servos();

  update_timer.setInterval(update_period, update_server);

  pinMode(temp_input_pin, INPUT);

  pinMode(light_status_pin, OUTPUT);
  pinMode(aircon_status_pin, OUTPUT);
}

void loop()
{
  Blynk.run();
  update_timer.run();
  servo_reset_timer.run();

  digitalWrite(light_status_pin, isLightOn);
  digitalWrite(aircon_status_pin, isAirconOn);
}

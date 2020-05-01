#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <Servo.h>
#include <LiquidCrystal.h>

#include "header.h" // imports auth, ssid and pass stored in header.h

// PIN USAGE
// Digital Pins ================================================================
const int light_status_pin = 2;         // D2: isLightOn (Trigger)
const int aircon_status_pin = 3;        // D3: isAirconOn (Echo)
const int LCD_d4 = 4;                   // D4 to D10: LCD Display
const int LCD_d5 = 5;
const int LCD_d6 = 6;
const int LCD_d7 = 7;
const int LCD_RS = 8;
const int LCD_EN = 9;
const int LCD_BL = 10;
                                        // D11: (PIR Sensor)
const int RX_pin = 12;                  // D12: WiFi RX
const int TX_pin = 13;                  // D13: WiFi TX
// Analog Pins -----------------------------------------------------------------
const int LCD_button_pin = A0;          // A0: LCD Shield Buttons
const int temp_sensor_pin = A1;         // A1: Temperature Sensor
                                        // A2: (LDR?)
const int lightOn_servo_pin = A3;       // A3: Light On Servo
const int lightOff_servo_pin = A4;      // A4: Light Off Servo
const int aircon_servo_pin = A5;        // A5: Aircon Toggle Servo
// -----------------------------------------------------------------------------
// V0: isLightOn (0 or 255 - can use with Blynk LED)
// V1: isAirconOn (0 or 255 - can use with Blynk LED)
// V2: Temperature Reading
// V9: Light Control (from app / Google Assistant)
// V11: Aircon Control (from app / Google Assistant)

//////////////////// WiFi Shield Setup ////////////////////
extern const char auth[];
extern const char ssid[];
extern const char pass[];

#include <SoftwareSerial.h>
SoftwareSerial EspSerial(RX_pin, TX_pin); // RX, TX

#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);

//////////////////// LCD Shield Setup ////////////////////
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_d4, LCD_d5, LCD_d6, LCD_d7);

int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 // For V1.1 us this threshold
 if (adc_key_in < 50)   return btnRIGHT;
 if (adc_key_in < 250)  return btnUP;
 if (adc_key_in < 450)  return btnDOWN;
 if (adc_key_in < 650)  return btnLEFT;
 if (adc_key_in < 850)  return btnSELECT;
 
 return btnNONE;  // when all others fail, return this...
}

//////////////////// Variable Definitions ////////////////////
BlynkTimer timer;
void update_server();
long update_period = 10000L; // server is updated every 10s

float temp_c;
float temp_vout;
void update_temp();
void change_aRef_to_1p1();
void change_aRef_to_5p0();
void update_aRef_1p1();
void update_aRef_5p0();
void reset_aRef();
float aRef_value = 5.0; // Normal: 5.0, Temperature Reading: 1.1, Transition: 0.0

void switch_on_lights();
void switch_off_lights();
void switch_on_aircon();
void switch_off_aircon();

Servo lightOn_servo, lightOff_servo, aircon_servo;
void reset_servos();
void attach_servos();
void detach_servos();
long servo_reset_time = 2000L;
long servo_detach_time = 1000L;

int isLightOn, isAirconOn;

//////////////////// Blynk Commands ////////////////////
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
    switch_on_lights();
  }

  else if(param.asInt() == 0){
    switch_off_lights();
  }
}

BLYNK_WRITE(V11){
  if(param.asInt() == 1 && isAirconOn == 0){
    switch_on_aircon();
  }

  else if(param.asInt() == 0 && isAirconOn == 1){
    switch_off_aircon();
  }
}

//////////////////// Self-declared Functions ////////////////////
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

void update_server(){
  change_aRef_to_1p1();
  update_status();
  timer.setTimeout(100, update_temp);
  timer.setTimeout(200, change_aRef_to_5p0);
}

void change_aRef_to_1p1(){
  aRef_value = 0.0; //transition value

  analogReference(INTERNAL);
  analogRead(temp_sensor_pin);
  timer.setTimeout(100, update_aRef_1p1);
}

void change_aRef_to_5p0(){
  aRef_value = 0.0; //transition value

  analogReference(DEFAULT);
  analogRead(temp_sensor_pin);
  timer.setTimeout(100, update_aRef_5p0);
}

void update_aRef_1p1(){
  aRef_value = 1.1;
}

void update_aRef_5p0(){
  aRef_value = 5.0;
}

void update_status(){
  Blynk.virtualWrite(V0, isLightOn*255);
  Blynk.virtualWrite(V1, isAirconOn*255);
}

void update_temp(){
  temp_vout = analogRead(temp_sensor_pin);
  temp_c = (temp_vout*110)/1023;

  Blynk.virtualWrite(V2, temp_c);
}

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

//////////////////// Arduino Setup and Loop ////////////////////
void setup(){
  EspSerial.begin(ESP8266_BAUD); // Set ESP8266 baud rate
  delay(10);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("L: ");
  lcd.setCursor(8, 0);
  lcd.print("AC: ");
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.setCursor(10, 1);
  lcd.print((char)223);
  lcd.print("C");

  Blynk.begin(auth, wifi, ssid, pass);

  reset_servos();

  timer.setInterval(update_period, update_server);

  pinMode(temp_sensor_pin, INPUT);

  pinMode(light_status_pin, OUTPUT);
  pinMode(aircon_status_pin, OUTPUT);
}

void loop(){
  Blynk.run();
  timer.run();

  lcd.setCursor(3, 0);
  if (isLightOn == 0){
    lcd.print("Off");
  }
  else if (isLightOn == 1){
    lcd.print("On ");
  }
  
  lcd.setCursor(12, 0);
  if (isAirconOn == 0){
    lcd.print("Off");
  }
  else if (isAirconOn == 1){
    lcd.print("On ");
  }
  
  lcd.setCursor(6, 1);
  lcd.print(temp_c);
  lcd.setCursor(10, 1);
  lcd.print((char)223);
  lcd.print("C    ");

  digitalWrite(light_status_pin, isLightOn);
  digitalWrite(aircon_status_pin, isAirconOn);
}

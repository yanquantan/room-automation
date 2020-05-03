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
// Virtual Pins ----------------------------------------------------------------
// V0: isLightOn (0 or 255 - can use with Blynk LED)
// V1: isAirconOn (0 or 255 - can use with Blynk LED)
// V2: Temperature Reading
// V9: Light Control (from app / Google Assistant)
// V11: Aircon Control (from app / Google Assistant)

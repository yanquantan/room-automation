// Digital Pins ================================================================

                                        // D3: Door Sensor (?)
const int LCD_d4 = 4;                   // D4 to D10: LCD Display
const int LCD_d5 = 5;
const int LCD_d6 = 6;
const int LCD_d7 = 7;
const int LCD_RS = 8;
const int LCD_EN = 9;
const int LCD_BL = 10;
                                        // D11: Temperature Sensor
                                        // D12: WiFi RX
                                        // D13: WiFi TX
// Analog Pins -----------------------------------------------------------------
const int LCD_button_pin = A0;          // A0: LCD Shield Buttons
const int temp_sensor_pin = A1;         // A1: Temperature Sensor
const int lightBOn_servo_pin = A2;      // A2: Light B On Servo
const int lightAOn_servo_pin = A3;      // A3: Light A On Servo
const int lightBOff_servo_pin = A4;     // A4: Light B Off Servo
const int lightAOff_servo_pin = A5;     // A5: Light A Off Servo
// Virtual Pins ----------------------------------------------------------------
// V0: isLightOn (0 or 1)
// V1: isAirconOn (0 or 1)
// V2: Temperature Reading
// V9: Light A Control (from app / Google Assistant)
// V11: Light B Control (from app / Google Assistant)

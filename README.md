# Arduino-based IOT Room Automation
Are you trying to automate your room? Want to switch off your lights / aircon from your phone or simply by giving Google Assistant commands? You've come to the right place! Read on to find out how to use an Arduino Uno (or any other Arduino compatible) to control your light and aircon switches!

Note: You need to have your own WiFi network (NUS_STU does **not** work) - personal hotspot from your phone works

## Version 1.0
This version is developed for use in RC4 rooms, and is able to control (via Blynk app):
* 1 x light switch
* 1 x aircon on/off button

Version 1.0 _optional_ features include:
* LCD display showing:
  * Light and aircon status (on / off)
  * Temperature reading
* Analog temperature sensor (up to 0.1 deg C precision)

Version 1.0 limitations:
* LCD shield buttons **cannot** be used because LM35 temperature sensor operates at reference voltage 1.1V

### Hardware Requirements
This project will require the following hardware (which can be purchased from [sg.cytron.io](https://sg.cytron.io/)):
* [Maker Uno](https://sg.cytron.io/p-maker-uno-simplifying-arduino-for-education) (or any other Arduino compatible)
* [WiFi Shield](https://sg.cytron.io/p-cytron-esp8266-wifi-shield)
* [LCD Shield](https://sg.cytron.io/p-lcd-keypad-shield) (optional)
* [LM35 Analog Temperature Sensor](https://sg.cytron.io/p-lm35-analog-temperature-sensor-module) (optional)
* [Micro Servo (180 deg)](https://sg.cytron.io/p-towerpro-sg90-micro-servo) x 3
* Miscellanous Items
  * [Small Breadboard](https://sg.cytron.io/p-breadboard-8.5x5.5cm-400-holes)
  * [Jumper Wires](https://sg.cytron.io/p-male-to-male-jumper-wire)
  * [Battery Holder](https://sg.cytron.io/p-4xaaa-battery-holder)
  * AAA Batteries x 4 (or AA Batteries)
  * MicroUSB Cable
  * Powerbank (at least 10,000 mAh recommended) OR nearby USB power supply
  * 3M Command Refill Strips (Mini) x 3
* Optional Items
  * [Acrylic Base Plate](https://sg.cytron.io/p-acrylic-base-plate-for-arduino-uno)
  * [Breadboard Jumper Wire Kit](https://sg.cytron.io/p-breadboard-jumper-wire-kit-140pcs)

### Software Requirements
You will need to install the following software:
* On your computer: [Arduino IDE](https://www.arduino.cc/en/main/software) with the following libraries:
  * [LiquidCrystal Library](https://www.arduino.cc/en/Reference/LiquidCrystal)
  * [Servo Library](https://www.arduino.cc/en/Reference/Servo)
  * [ESP8266 Library](https://github.com/vshymanskyy/BlynkESP8266)
  * [Blynk Library](http://help.blynk.cc/en/articles/512105-how-to-install-blynk-library-for-arduino-ide)
* On your phone: [Blynk](https://blynk.io/en/getting-started)

## Quick Start
1. Create an account with Blynk, sign in and scan the QR code below using your phone:

![](/rc4-room/resources/blynk_QR.jpg)

2. Press the settings logo (the hexagon), copy the Auth Token onto your clipboard, and send it to yourself


3. Rename the file `b_wifi_config_sample.h` to `b_wifi_config.h`, replacing the 3 key information as required:
 * Auth Token (given by Blynk)
 * WiFi network name
 * WiFi network password (leave blank if it's an open network)


4. Upload the code onto your Maker UNO using Arduino IDE


5. Set up the hardware according to the schematic below:
 * Note: Stack the shields as follows:
    * Bottom: Maker UNO
    * Middle: WiFi Shield
    * Top: LCD Shield
 * Ensure that the temperature sensor is facing upwards
 * Ensure that the mini-jumpers on the WiFi shield are placed at D13 and D12
 * If required, turn off the Buzzer by shifting the switch on the Maker UNO

![](/rc4-room/resources/v1_1.jpg)

6. Power on your Maker UNO using your Powerbank / USB power supply


7. Stick the servo motors onto the respective switches **in the correct orientation** (please check before sticking):
 * Servo 1: Light On
 * Servo 2: Light Off
 * Servo 3: Aircon Button


8. Voila! You're done!

## Extension: Google Assistant Control (work in progress)
### Additional Features
* Control of light / aircon by Google assistant

### Additional Software Requirements
 * [IFTTT](https://ifttt.com/)

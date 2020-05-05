const char auth[] = "YourAuthTokenHere"; // get this from your Blynk app
const char ssid[] = "YourWiFiSSIDHere"; // this is the name of your WiFi network
const char pass[] = "YourWiFiPasswordHere"; // this is the WiFi password

#include <SoftwareSerial.h>
SoftwareSerial EspSerial(RX_pin, TX_pin); // RX, TX

#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);

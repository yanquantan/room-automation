#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire(temp_sensor_pin);
DallasTemperature ds18b20(&oneWire);

void setup_temp(){
  ds18b20.begin();
}

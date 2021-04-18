/**********************************************
Copyright 2020 -2021, (c) The Eichen Group.
Acknowledgement(s): Daniel Ogunlolu, AmazingTech (R)
***********************************************/

#include <sensors.hpp>


irSensor ir (12, LOW);
//First number is the pin the infrared sensor is connected to,
//second number is the active operating state of the ir sensor.


void setup()
{
  ir.begin()
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()

{
  //Toggle the built-in LED when an item is detected by the ir sensor:
  ir.toggle(LED_BUILTIN);
  delay(1000);
  ir.toggle(LED_BUILTIN);
  delay(1000);


}

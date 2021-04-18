/**********************************************
Copyright 2020 -2021, (c) The Eichen Group.
Acknowledgement(s): Daniel Ogunlolu, AmazingTech (R)
***********************************************/
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <sensors.hpp>
ultrasonicSensor ultra (7,8);    //First argument is the trigger pin, second is echo pin.

void setup()
{
  ultra.begin();
  Serial.begin(9600);
}

void loop()
{
  int distance = ultra.getDistance_cm();    //Measure distance in centimetres (cm)

  Serial.print("The distance is: ");
  Serial.println(distance);
  delay(1000);
}

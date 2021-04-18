////////////////////////////////////////////////////////////////////////////////////////////////////
//*FILE NAME:       ultrasonicSensor.cpp
//*FILE DESC:       Source file for sensor library.
//*FILE VERSION:    1.1
//*FILE AUTHOR:     The Eichen Group
//*CONTRIBUTORS:    Chimaroke Okwara(code),
//                  Ogunlolu Daniel(creative)
//*LICENSE:         Academic Free License.
//*LAST MODIFIED:   Friday, 16 April 2021 19:10
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include <stdint.h>
#include <sensors.hpp>

void ultrasonicSensor::begin()
{
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
}

bool ultrasonicSensor::detect_mm(float &distance)
{
  return ((getDistance_mm() >= distance) ? (true) : (false));
}

bool ultrasonicSensor::detect_cm(float &distance)
{
  return ((getDistance_cm() >= distance) ? (true) : (false));
}

bool ultrasonicSensor::detect_m(float &distance)
{
  return ((getDistance_m() >= distance) ? (true) : (false));
}


float ultrasonicSensor::getDistance_m() const
{
  //Generate pulse:
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);

  float pulseDur {pulseIn(EchoPin, HIGH)};
  return ((pulseDur*340)/2000000);
}

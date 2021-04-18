////////////////////////////////////////////////////////////////////////////////////////////////////
//*FILE NAME:       sensors.hpp
//*FILE DESC:       Header file for sensor library.
//*FILE VERSION:    1.1
//*FILE AUTHOR:     The Eichen Group
//*CONTRIBUTORS:    Chimaroke Okwara(code),
//                  Ogunlolu Daniel(creative)
//*LICENSE:         Academic Free License.
//*LAST MODIFIED:   Friday, 16 April 2021 19:10
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Arduino.h>
#include <stdint.h>
#ifndef _SENSORS_
#define _SENSORS_


class irSensor
{
public:
	irSensor(const uint8_t &sensorPin, const uint8_t &operationState)
          :SensorPin {sensorPin}, OperationState {operationState}
  { }
  irSensor(const uint8_t &sensorPin)
          :irSensor {sensorPin, LOW}
  { }

  void begin();

  bool detect(void);
  void toggle(uint8_t &outPin);

private:
	uint8_t SensorPin {}, OperationState {};

};

class ultrasonicSensor
{
public:
  ultrasonicSensor(const uint8_t &trigPin, const uint8_t &echoPin)
                :EchoPin {echoPin}, TrigPin {trigPin}
  { }

  void begin();

  bool detect_m(float &distance);
  bool detect_cm(float &distance);
  bool detect_mm(float &distance);

  float getDistance_m(void)const;
  float getDistance_cm(void)const { return (getDistance_m()*100); }
  float getDistance_mm(void)const { return (getDistance_m()*1000); }

private:
  uint8_t EchoPin {}, TrigPin {};
};

#endif

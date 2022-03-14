////////////////////////////////////////////////////////////////////////////////////////////////////
//*FILE NAME:       main.cpp
//*FILE DESC:       Source file for Konvei.
//*FILE VERSION:    0.1.1
//*FILE AUTHOR:     Chimaroke Okwara
//*LAST MODIFIED:   Friday, 16 April 2021 11:51
//*LICENSE:         Academic Free License
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include <stdint.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <sensors.hpp>
#include <pincontrol.hpp>

//Pins for LCD screen:
LiquidCrystal lcd {7,8,9,10,11,12};

//Infrared sensor:
irSensor ir {5};

//Ultrasonic sensor:
ultrasonicSensor ultra {13, 14};

//Buzzer pin:
outputPin buzzer {15};

//Motor pin:
outputPin motor {5};

//Variables for calculating object height:
float itemDistance {0.0};     //Distance between the item and the ultrasonic sensor.
float refHeight {30.0};       //Distance between the conveyor floor and the ultrasonic sensor.
float itemHeight {0.0};       //Item calculated height i.e   refHeight-itemDistance.
uint32_t totalCount {0l};     //Count of accepted objects.

const float allowedHeight {20.0};   //Allowed height for items.

void setup()
{
  //Initialise LCD screen and sensors:
  lcd.begin(16, 2);
  ir.begin();
  ultra.begin();
  buzzer.set();
  motor.set();
  motor.write(1);


  //To deactivate LED on the Arduino Uno
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite (LED_BUILTIN, LOW);

  //Print Welcome Message
  lcd.setCursor(0, 0);
  lcd.print("Eichen(R)");
  delay(3000);

  lcd.clear();

  lcd.setCursor(0, 0);

  lcd.print("CONVEYOR BELT SYSTEM WITH FOREIGN BODY DETECTION AND ALERT");
  for(size_t i{}; i<42; ++i)
  {
    lcd.scrollDisplayLeft();
    delay(200);
  }
  delay(300);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Starting motor...");
  motor.write(0);
  lcd.clear();

  //H stands for HEIGHT
  lcd.setCursor(0,1);
  lcd.print("H:    ");

  //No is for counting permitted items.
  lcd.setCursor(7,1);
  lcd.print("No:    ");
}



void loop()
{
  if (ir.detect()) //when an object is detected by the irsenor...
  {
    motor.write(0);
    itemDistance = ultra.getDistance_cm();
    itemHeight   = refHeight - itemDistance;

    //now display object height

    lcd.setCursor(3,1);
    lcd.print(itemHeight);

    if ((itemHeight >= allowedHeight))
    {
       ++totalCount;
       lcd.setCursor(11,1);
       lcd.print(totalCount);
       delay (1000);

       lcd.setCursor(0,0);
       lcd.print("STATUS:  WAITING...");
       lcd.setCursor(0,1);
       lcd.print("HEIGHT:      CM");

    }

    else
    {

          lcd.setCursor(9,1);
          lcd.print("REJECTED..");
          motor.write(1); //stop motor
          lcd.setCursor(9,0);
          lcd.print("STOPPED");
          buzzer.write(1); //start buzzer

          while (ir.detect())      //As long as the item is not removed...
            ;             //...do nothing.

    }

       buzzer.write(0);
       motor.write(0);

  }




  else                    //When no object is detected...
    ;                     //...do nothing.
}

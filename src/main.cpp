////////////////////////////////////////////////////////////////////////////////////////////////////
//*FILE NAME:       main.cpp
//*FILE DESC:       Source file for Konvei.
//*FILE VERSION:    0.1.0
//*FILE AUTHOR:     Chimaroke Okwara
//*LAST MODIFIED:   
//*LICENSE:         MIT License
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <sensorLib.hpp>

//Pins for LCD screen:
LiquidCrystal lcd (7,8,9,10,11,12);

//Buzzer pin:
const uint8_t buzzer = 15;

//Infrared sensors:
irSensor ir1(5, LOW), ir2(6, LOW);

//Ultrasonic sensor
ultrasonicSensor ultra(13, 14);

//Motor pin:
const uint8_t motor = 5;

//Variables for calculating object height:
float itemDistance;     //Distance between the item and the ultrasonic sensor
float refHeight = 30;   //Distance between the conveyor floor and the ultrasonic sensor
float itemHeight = 0;   //Item calculated height i.e   refHeight-itemDistance
long totalCount = 0;    //Count of accepted objects.

void setup();
void loop();


void setup()
{
  //Initialise LCD screen
  lcd.begin(16, 2);

  //Pin connected to buzzer
  pinMode(buzzer,OUTPUT);

  //Pin connected to motor
  pinMode(motor,OUTPUT);

  //  digitalWrite(motor,HIGH);


  //To deactivate LED on the Arduino Uno
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite (LED_BUILTIN, LOW);

  //Print Welcome Message for 3 sec
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
  }  delay(3000);

  lcd.clear();

  //Switch on the motor
  digitalWrite(motor,LOW);

  //Display message
  lcd.setCursor(0,0);
  lcd.print("MOTOR:   MOVING");

  //H stands for HEIGHT
  lcd.setCursor(0,1);
  lcd.print("H:    ");

  //No is for the counting of objects
  lcd.setCursor(7,1);
  lcd.print("No:    ");
}



void loop()
{
  if (ir1.detect()) //when an object is detected by the irsenor1
  {
      itemDistance = ultra.getDistance_cm();
      itemHeight   = refHeight - itemDistance;

      //now display object height

      lcd.setCursor(0,1);
      lcd.print("H:    ");
      lcd.setCursor(3,1);
      lcd.print(itemHeight);

      if ( itemHeight >= 20.0) //if the object height is up to or equals 20cm
      {
         totalCount++;
         lcd.setCursor(11,1);
         lcd.print(totalCount);
         delay (1000);

         lcd.setCursor(0,0);
         lcd.print("STATUS:  WAITING...");
         lcd.setCursor(0,1);
         lcd.print("HEIGHT:      CM");

      }

      else  //if the object height is less than 20cm
        //and the object is still in front of the sensors
      {

            lcd.setCursor(9,1);
            lcd.print("REJECTED..");
            digitalWrite(motor, HIGH); //stop motor
            lcd.setCursor(9,0);
            lcd.print("STOPPED");
            digitalWrite(buzzer, HIGH); //start buzzer

            while (ir2.detect())      //As long as the item is not removed...
              delay(100);             //...do nothing.

      }

         digitalWrite(buzzer,LOW);
         digitalWrite(motor, LOW);

  }




  else                    //When no object is detected...
    delay(100);           //...do nothing.
}

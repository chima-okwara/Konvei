///////////////////////////////////////////////////////////////////////////////
//Design and construction of Belt Conveyor
//With Automatic Foreign Body Detection and Alert SYSTEM
//Written by Chima Okwara, Eichen(R)
//c. March 2019
//***************************************************************************//
//Acknowledgement:
//Daniel Ogunlolu, AmazingTech(R)
//c. 2018
///////////////////////////////////////////////////////////////////////////////
#include "Arduino.h"
#include "LiquidCrystal.h"
#include "Wire.h"

LiquidCrystal lcd (7,8,9,10,11,12); //Original project used LCD 20*4
                                    //We are using LCD 1602

//////////////Pins for all electronic devices://///////////////////////////////
//Ultrasonic pins//////////////////////////////////////////////////////////////
const int echo = 13;////////////////////////////////////////////////////////////
const int trig = 14;////////////////////////////////////////////////////////////
/*****************************************************************************/
//Buzzer pin///////////////////////////////////////////////////////////////////
const int buzzer = 15;//////////////////////////////////////////////////////////
/*****************************************************************************/
//Infrared sensor pins/////////////////////////////////////////////////////////
const int sensor1 = 4; //1st infrared sensor, for sensing presence of item//////
const int sensor2 = 6; //2nd infrared sensor, for sensing removal of item///////
/*****************************************************************************/
//Motor pin
const int motor = 5;////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


//////////////Variables for calculating object height///////////////////////////
float itemDistance; //distance between the item and the ultrasonic//////////////
long duration; //sound wave goes from ultrasonic sensor to item, to and fro/////
float height = 0;// object calculated height i.e   refHeight minus itemDistance/
float refHeight = 30;  //distance between the conveyor floor and the ultrasonic/
int totalCount = 0;  //count of objects on conveyor/////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void setup()
{
  //Initialise LCD screen
  lcd.begin(16, 2);

////Set modes for all devices///////////////////////////////////////////////////
  //Pin connected to buzzer
  pinMode(buzzer,OUTPUT);

  //Ultrasonic sensor pins
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);

  //Pin connected to motor
  pinMode(motor,OUTPUT);
//  digitalWrite(motor,HIGH); //to be edited later

  //Pin connected to infrared sensors
  pinMode(sensor1,INPUT);
  pinMode(sensor2,INPUT);


  //To deactivate LED on the Arduino Uno////////////////////////////////////////
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite (LED_BUILTIN, LOW);
  //////////////////////////////////////////////////////////////////////////////

  //Print Welcome Message for 3 sec/////////////////////////////////////////////
  lcd.setCursor(0, 0);
  lcd.print("Eichen(R)");
  delay(3000);


//  lcd.setCursor(0, 0);
//  lcd.print(" PN-CTE-16-0369 ");
//
//  lcd.setCursor(0, 1);
//  lcd.print(" PN-CTE-16-0384 ");
//  delay(3000);



  lcd.clear();

  lcd.setCursor(0, 0);

  lcd.print("CONVEYOR BELT SYSTEM WITH FOREIGN BODY DETECTION AND ALERT");
  lcd.scrollDisplayLeft();
  delay(3000);

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



/// These were optimised for a 20x4 display.
//  lcd.setCursor(0,1);
//  lcd.print("HEIGHT:   ");
//  lcd.setCursor(0,1);
//  lcd.print("COUNT:   0");
// lcd.setCursor(0,1);
// lcd.print("STATUS:  WAITING...");
}



void loop()
{
  if (digitalRead(sensor1)==LOW) //when an object is detected by the irsenor1
  {
//      delay(1000);
//      wait for some second before calculating
//      height.....for object to reach like center of sensors
      digitalWrite(trig, LOW);
      delay(100);
      digitalWrite(trig, HIGH);
      delay(1000);
      digitalWrite(trig, LOW);

      duration = pulseIn (echo, HIGH);
      itemDistance = (duration*340)/20000;
      height   = refHeight - itemDistance;

      //now display object height

      lcd.setCursor(0,1);
      lcd.print("H:    ");
      lcd.setCursor(3,1);
      lcd.print(height);

      if ( height >= 20) //if the object height is up to or equals 20cm
      {   //valid height is 20 or more
         totalCount++;
         lcd.setCursor(11,1);
         lcd.print(totalCount);
//         lcd.setCursor(9,1);
//         lcd.print("ACCEPTED..");


         //time for object to stay under ultrasonic sensor...
         //adjust later depending on motor speed

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

            while (digitalRead(sensor2)==LOW)
            delay(100);

      }

         digitalWrite(buzzer,LOW); //off buzzer
         digitalWrite(motor, LOW); //start motor back


//         lcd.setCursor(9,0);
//         lcd.print("MOVING ");
//         lcd.setCursor(0,1);
//         lcd.print("STATUS:  WAITING...");
//         lcd.setCursor(0,1);
//         lcd.print("HEIGHT:      CM");
  }




  else //when no object is detected
  {
    delay(100);
  }
}

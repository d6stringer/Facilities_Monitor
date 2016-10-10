/*
Reel Solar Power, Inc.
Author: Daniel Woodson
Start Date: 20160928
*/

// built from examples:
// www.ladyada.net/learn/sensors/thermocouple

#include "max6675.h"

//arduino uno setup
const int thermoDO = 4; //Thermocouple setup
const int thermoCS = 5; //Thermocouple setup
const int thermoCLK = 6; //Thermocouple setup
const int overTEMP = 13; //can change to regular variable later but might be nice to keep
const int errorRelay = 8; //digital output to alarm relay
const int vccPin = 3; //can eliminate later
const int gndPin = 2; //can eliminate later
const int vccPin2 = 9; //can eliminate later
const int silencePin = 10; //digital input to silence alarm button

//variables
char* errorStr[] = {"Low Air Pressure", "High Water Temperature", "Vacuum Pressure High" , "Thermocouple Broken!"};
float highTemp = 30.0; //Cooling Loop High Temperature Set Point
float resetTemp = 29.5; //Cooling Loop Reset Temperature Set Point


MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO); //Thermocouple setup


void thermocoupleRead() {
  // read the parameters, alarm if out of spec.
  static int counter = 0;
  static int silence = 0; 
  static int error = 0;

    counter = counter + 1;
    if (counter == 100){
      counter = 0;
           if (thermocouple.readCelsius() < resetTemp){
             
             digitalWrite(overTEMP, LOW);
             digitalWrite(errorRelay, HIGH); //this turns the alarm off if the temp goes below the reset value
             silence = 0;
             error = 0;
             Serial.print("Error is ");
             Serial.println(error);
             Serial.print("Silence is ");
             Serial.println(silence);
             }
           
           else if (thermocouple.readCelsius() > highTemp){
             error = 1;
             Serial.println(errorStr[1]);
             digitalWrite(overTEMP, HIGH);
             Serial.print("Error is ");
             Serial.println(error);
             Serial.print("Silence is ");
             Serial.println(silence);
             }

           else if (isnan(thermocouple.readCelsius())){
             error = 2;
             Serial.println(errorStr[3]);
             Serial.print("Error is ");
             Serial.println(error);
             Serial.print("Silence is ");
             Serial.println(silence);
             }
           
      Serial.print("C = "); 
      Serial.println(thermocouple.readCelsius()); //outputs chilled water temperature to serial interface
      
      if (digitalRead(silencePin) == LOW){
       digitalWrite(errorRelay, HIGH); //This turns the alarm off with the silence button
       silence = 1;
       }
         
      if ((error != 0) && (silence == 0)){
       digitalWrite(errorRelay, LOW); //this turns the alarm on
       }
      if (error-1 != 0){
        silence = 0;
        } 
    }
           
}

  
void setup() {
  Serial.begin(9600);
  // use Arduino pins 
  pinMode(vccPin, OUTPUT); digitalWrite(vccPin, HIGH); //can eliminate later
  pinMode(gndPin, OUTPUT); digitalWrite(gndPin, LOW); //can eliminate later
  pinMode(vccPin2, OUTPUT); digitalWrite(vccPin2, LOW); //can eliminate later
  pinMode(silencePin, INPUT); digitalWrite(silencePin, HIGH);
  pinMode(overTEMP, OUTPUT); digitalWrite(overTEMP, LOW);
  pinMode(errorRelay, OUTPUT); digitalWrite(errorRelay, HIGH);
  
  Serial.println("Welcome to the THUNDERDOME!!!");
  Serial.println("MAX6675 test");
  // wait for MAX chip to stabilize
  delay(500);
}

void loop() {
 
  thermocoupleRead();
    delay(10);
   
}

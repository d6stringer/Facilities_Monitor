/*
Reel Solar Power, Inc.
Author: Daniel Woodson
Start Date: 20160928
*/

// built from examples:
// www.ladyada.net/learn/sensors/thermocouple

#include "max6675.h"

//arduino mega 2560 setup
const int thermoDO = 4; //Thermocouple setup
const int thermoCS = 5; //Thermocouple setup
const int thermoCLK = 6; //Thermocouple setup
const int overTEMP = 22; //can change to regular variable later but might be nice to keep. 13 on uno
const int errorRelay = 23; //digital output to alarm relay. 8 on uno
const int vccPin = 3; //can eliminate later
const int gndPin = 2; //can eliminate later
const int vccPin2 = 9; //can eliminate later
const int silencePin = 24; //digital input to silence alarm button. 10 on uno
const int lowPRESSURE= 25;// 
const int errorRelay1 = 26; //Digital output to low air pressure alarm relay. 9 on uno
unsigned long previousMillis = 0;
//variables
char* errorStr[] = {"Low Air Pressure", "High Water Temperature", "Vacuum Pressure High" , "Thermocouple Broken!"};
float highTemp = 30.0; //Cooling Loop High Temperature Set Point
float resetTemp = 29.5; //Cooling Loop Reset Temperature Set Point
float LowAirPressure = 95; // Low Air Pressure


MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO); //Thermocouple setup


void thermocoupleRead() {
  // read the parameters, alarm if out of spec.
  static int counter = 0;
  static int silence = 0; 
  static int error = 0;
  static int lasterror = 0;
  

    counter = counter + 1;
    if (counter == 100){
      counter = 0;
           if (thermocouple.readCelsius() < resetTemp){
             
             digitalWrite(overTEMP, LOW);
             digitalWrite(errorRelay, HIGH); //this turns the alarm off if the temp goes below the reset value
             silence = 0;
             error = 0;
             lasterror = 0;
             }
           else if (thermocouple.readCelsius() > highTemp){
             error = 1;
             if (silence == 1){
               lasterror = error;
               silence = 0;
               }
             Serial.println(errorStr[1]);
             digitalWrite(overTEMP, HIGH);
             }
           else if (isnan(thermocouple.readCelsius())){
             error = 2;
             if (silence == 1){
               lasterror = error;
               silence = 0;
               }
             Serial.println(errorStr[3]);
             }
      Serial.print("C = "); 
      Serial.println(thermocouple.readCelsius()); //outputs chilled water temperature to serial interface
      
      if (digitalRead(silencePin) == LOW){
         digitalWrite(errorRelay, HIGH); //This turns the alarm off with the silence button
         silence = 1;
         }
      if (lasterror != error) {
       digitalWrite(errorRelay, LOW); //this turns the alarm on
       
       } 

    }
     
}

void AirPressureMonitor () {
float AirPressure = analogRead(A0)*0.246-24.955; //Convert Analog values to psi
static int counter = 0;
static int error = 0;
static int lasterror = 0;
static int silence = 0; 
counter = counter + 1;

  if(counter == 100) {
    counter = 0;
    if (AirPressure < LowAirPressure){
    error = 3;
     if (silence == 1){
           lasterror = error;
            silence = 0;
               }
    digitalWrite(lowPRESSURE, LOW); // Low Air Pressure Alarm. Change to error relay? 
    Serial.println(errorStr[0]);
    }
    if (AirPressure > LowAirPressure) {
      digitalWrite(lowPRESSURE, HIGH); // Do nothing. This part of the code will have to be tested. 
      silence = 0;
      error = 0;
      lasterror = 0;
    }
      Serial.print("Air Pressure =  ");
      Serial.println(AirPressure); // Just printing the air pressure values
     
     if (digitalRead(silencePin) == LOW){// If button is pressed...
         digitalWrite(lowPRESSURE, HIGH); //This turns the alarm off with the silence button
         }
          if (lasterror != error) {
            digitalWrite(lowPRESSURE, LOW); //this turns the alarm on
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
  pinMode(lowPRESSURE, OUTPUT); // Low Air pressure Alarm
  Serial.println("Welcome to the THUNDERDOME!!!");
  Serial.println("MAX6675 test");
  // wait for MAX chip to stabilize
  delay(500);
}

void loop() {
 
  thermocoupleRead();
    delay(10);
    AirPressureMonitor();
    delay(10);
   
}

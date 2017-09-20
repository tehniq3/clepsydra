/*
 base sketch: https://cdn.sparkfun.com/datasheets/Components/LED/_7Seg_Example.pde
 4 digit 7 segment display: http://www.sparkfun.com/products/9483 
 7 segments + 4 digits + 1 colon = 12 pins required for full control 
modified connexion by Nicu FLORICA (niq_ro) from http://nicuflorica.blogspot.com
http://arduinotehniq.blogspot.com
http://www.tehnic.go.ro
http://www.arduinotehniq.com/

CLEPSYDRA - write by Nicu FLORICA (niq_ro) for Biyachie
ver.1 - initial version
*/

#include "EEPROM.h"// http://tronixstuff.com/2011/03/16/tutorial-your-arduinos-inbuilt-eeprom/

int digit1 = 11; //PWM pin for control digit 1 (left side)
int digit2 = 10; //PWM pin for control digit 2
int digit3 = 9;  //PWM pin for control digit 3
int digit4 = 6;  //PWM pin for control digit 4 (right side)

int segA = 2; // pin for control "a" segment
int segB = 3; // pin for control "b" segment
int segC = 4; // pin for control "c" segment
int segD = 5; // pin for control "d" segment
int segE = 12; // pin for control e" segment
int segF = 7; // pin for control "f" segment
int segG = 8; // pin for control "g" segment
int segDP = 13; // pin for control decimal point

#define uppin A0   // pin for increase value (+)  (A0---SW0---GND)
#define setpin A1   // pin for MENU/change (A1---SW1--GND)
#define downpin A2   // pin for decrease value (-) (A2---SW2---GND)
#define start1 A3   // pin for start1 type (A3---SW3---GND)
#define start2 A4   // pin for start2 type (A4---SW4---GND)
#define ledpin A5   // pin for control LED (A5---LED--220R--GND)


int DISPLAY_BRIGHTNESS = 512;
//Display brightness
//Each digit is on for a certain amount of microseconds
//Then it is off until we have reached a total of 20ms for the function call
//Let's assume each digit is on for 1000us
//Each digit is on for 1ms, there are 4 digits, so the display is off for 16ms.
//That's a ratio of 1ms to 16ms or 6.25% on time (PWM).
//Let's define a variable called brightness that varies from:
//5000 blindingly bright (15.7mA current draw per digit)
//2000 shockingly bright (11.4mA current draw per digit)
//1000 pretty bright (5.9mA)
//500 normal (3mA)
//200 dim but readable (1.4mA)
//50 dim but readable (0.56mA)
//5 dim but readable (0.31mA)
//1 dim but readable in dark (0.28mA)

/*  
//for common catode
#define DIGIT_ON  HIGH
#define DIGIT_OFF  LOW
#define SEGMENT_ON  LOW
#define SEGMENT_OFF HIGH
*/

// for common anode
#define DIGIT_ON  LOW
#define DIGIT_OFF  HIGH
#define SEGMENT_ON  HIGH
#define SEGMENT_OFF LOW

int timp = 10;
byte meniu = 0;  


void setup() {
  
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(segDP, OUTPUT);

  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);

 Serial.begin(9600);
 Serial.println("CLEPSYDRA by niq_ro");

 pinMode(uppin, INPUT);  //   (A0---SW0---GND)
 pinMode(setpin, INPUT);  //  (A1---SW1---GND) 
 pinMode(downpin, INPUT);  // (A2---SW2---GND) 
 pinMode(start1, INPUT);  //  (A3---SW3---GND) 
 pinMode(start2, INPUT);  //  (A4---SW4---GND) 

 digitalWrite(uppin, HIGH); // pull-ups on
 digitalWrite(setpin, HIGH);
 digitalWrite(downpin, HIGH);
 digitalWrite(start1, HIGH);
 digitalWrite(start2, HIGH);

pinMode(ledpin, OUTPUT); // control led 
digitalWrite(ledpin, HIGH);
delay(200);
digitalWrite(ledpin, LOW);
}

void loop() {


// display parts   
  displayNumber(meniu); 
     
if (!(digitalRead(uppin)))
 {
   meniu = 1; //get value 1
 }
if (!(digitalRead(setpin)))
 {
   meniu = 2; //get value 2
 }
if (!(digitalRead(downpin)))
 {
   meniu = 3; //get value 3
 }
if (!(digitalRead(start1)))
 {
   meniu = 4; //get value 4
 }
if (!(digitalRead(start2)))
 {
   meniu = 5; //get value 5
 }


} // end main program


//Given a number, turns on those segments
//If number == 10, then turn off number
void lightNumber(int numberToDisplay) {
  switch (numberToDisplay){

  case 0:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 1:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 2:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 3:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 4:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 5:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 6:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 7:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 8:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 9:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  // all segment are ON
  case 10:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;

    // degree symbol made by niq_ro
  case 11:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  // C letter made by niq_ro
  case 12:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_OFF);
    break;
  
  // H letter made by niq_ro
  case 13:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;
 
  // L letter made by niq_ro
  case 14:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  // A letter made by niq_ro
  case 15:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;
  
    // F letter made by niq_ro
  case 16:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;
    
  // n letter made by niq_ro
  case 17:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_ON);
    break;

    // o letter made by niq_ro
  case 18:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_ON);
    break;
 
 // "Y" letter made by niq_ro
  case 19:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  // "r" letter made by niq_ro
  case 20:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_ON);
    break;

  // "d" letter made by niq_ro
  case 21:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_ON);
    break;
 }
}


// display clock with second off
void displayNumber(int toDisplay) {
  for(int digit = 4 ; digit > 0 ; digit--) {

    //Turn on a digit for a short amount of time
    switch(digit) {
    case 1:
     digitalWrite(digit1, DIGIT_ON);
        digitalWrite(segDP, SEGMENT_OFF);
      break;
   case 2:
      digitalWrite(digit2, DIGIT_ON);
    digitalWrite(segDP, SEGMENT_OFF);
      break;
    case 3:
      digitalWrite(digit3, DIGIT_ON);
   digitalWrite(segDP, SEGMENT_OFF);
      break;
    case 4:
      digitalWrite(digit4, DIGIT_ON);
    digitalWrite(segDP, SEGMENT_OFF);
      break;
    }
    lightNumber(toDisplay % 10);
    toDisplay /= 10;
    delayMicroseconds(DISPLAY_BRIGHTNESS); 

     //Turn off all segments
    lightNumber(10); 
    digitalWrite(segDP, SEGMENT_OFF);
  
    delayMicroseconds(DISPLAY_BRIGHTNESS); 

    //Turn off all digits
    digitalWrite(digit1, DIGIT_OFF);
    digitalWrite(digit2, DIGIT_OFF);
    digitalWrite(digit3, DIGIT_OFF);
    digitalWrite(digit4, DIGIT_OFF);
    digitalWrite(segDP, SEGMENT_OFF);
}
} 

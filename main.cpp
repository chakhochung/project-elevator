/*

Name: Bryan Chung 
Student number: 0990458
School: Hogeschool Rotterdam

*/


#include <Arduino.h>


#define ON 0
#define OFF 1

int latchPin = 11; // connect to the ST_CP of 74HC595 (pin 3,latch pin)
int clockPin = 9;  // connect to the SH_CP of 74HC595 (pin 4, clock pin)
int dataPin = 12;  // connect to the DS of 74HC595 (pin 2)
int digit = 9; // display the digit
int IRSensor = 2; // connect ir sensor to arduino pin 2
int LED = 13; // conect Led to arduino pin 13

byte sevenSegDigits[10] = { B01111011   ,  // = 0
                            B00001001   ,  // = 1
                            B10110011   ,  // = 2
                            B10011011   ,  // = 3
                            B11001001   ,  // = 4
                            B11011010   ,  // = 5
                            B11111000   ,  // = 6
                            B00001011   ,  // = 7
                            B11111011   ,  // = 8
                            B11001011      // = 9
                           };
byte sevenSegDP = B00000100;  // = DP

byte sevenSegAlpha[] = {  B11101011   , // = A
                          B11111000   , // = b
                          B01110010   , // = C
                          B10111001   , // = d
                          B11110010   , // = E
                          B11100010   , // = F
                          B11011011   , // = g
                          B11101000   , // = h
                          B01100000     // = I   
};
/* ***********************************************************
 *                      Global Variables                     *
 * ********************************************************* */
bool bAddDecimalPoint = true;            // display state of show decimal point

/* ***********************************************************
 *                         Void setup                        *
 * ********************************************************* */
void setup() {
    // Set latchPin, clockPin, dataPin as output
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);

    pinMode (IRSensor, INPUT); // sensor pin INPUT
    pinMode (LED, OUTPUT); // Led pin OUTPUT
}

/* ***********************************************************
 *                         Functions                         *
 * ********************************************************* */ 
// display a alpha, binary value, or number on the digital segment display
void sevenSegWrite(byte digit, bool bDP = false, char switchValue='D') {
    /*       digit = array pointer or binary value, as a byte 
     *         bDP = true-include decimal point, as boolean
     * switchValue = 'A' alpha
     *               'B' binary
     *               'D' digits <default>, as char           */
    
    // set the latchPin to low potential, before sending data
    digitalWrite(latchPin, LOW);
     
    // the data (bit pattern)
    if (switchValue=='A'){
        // alpha
        shiftOut(dataPin, clockPin, MSBFIRST, sevenSegAlpha[digit]+(sevenSegDP*bDP)); 
    } else if (switchValue=='B'){
        // binary
        shiftOut(dataPin, clockPin, MSBFIRST, digit+(sevenSegDP*bDP));
    } else {
        // digits
        shiftOut(dataPin, clockPin, MSBFIRST, sevenSegDigits[digit]+(sevenSegDP*bDP));   
    }
 
    // set the latchPin to high potential, after sending data
    digitalWrite(latchPin, HIGH);
}

void sevenSegBlank(){
    // set the latchPin to low potential, before sending data
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, B00000000);  
    // set the latchPin to high potential, after sending data
    digitalWrite(latchPin, HIGH);
}

/* ***********************************************************
 *                         Void Loop                         *
 * ********************************************************* */
void loop() {
 
 

 

  int statusSensor = digitalRead (IRSensor);
  
  if (statusSensor == ON){
    digitalWrite(LED, HIGH); 
    sevenSegWrite(digit,bAddDecimalPoint); // turn on the 7 segement
  }
  
  else 
  {
    digitalWrite(LED, LOW); 
    sevenSegBlank(); // turn off the 7 segement
  }

     
}

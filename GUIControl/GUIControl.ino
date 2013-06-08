/*
  Serial Event example
 
 When new serial data arrives, this sketch adds it to a String.
 When a newline is received, the loop prints the string and 
 clears it.
 
 A good test for this is to try it with a GPS receiver 
 that sends out NMEA 0183 sentences. 
 
 Created 9 May 2011
 by Tom Igoe
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/SerialEvent
 
 */
#include "pitches.h"

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
char inChar;
int ledPin;

int melody[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 };

void setup() {
  ledPin =13;
  // initialize serial:
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);

  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    stringComplete = false;
    if(inChar == 'a'){

      digitalWrite(ledPin,HIGH);
      for (int thisNote = 0; thisNote < 8; thisNote++) {

        // to calculate the note duration, take one second 
        // divided by the note type.
        //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        int noteDuration = 1000/noteDurations[thisNote];
        tone(8, melody[thisNote],noteDuration);

        // to distinguish the notes, set a minimum time between them.
        // the note's duration + 30% seems to work well:
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        // stop the tone playing:
        noTone(8);
      }
    }
    else if(inChar == 'b'){
      digitalWrite(ledPin,LOW);
    }
  }
}
/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    inChar = (char)Serial.read(); 
    // add it to the inputString:
    //    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    //    if (inChar == '\n') {
    stringComplete = true;
    //    } 
  }
}





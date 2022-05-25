/*
  Melody

 Plays a melody

 circuit:
 * 8-ohm speaker on digital pin 8

 created 21 Jan 2010
 modified 30 Aug 2011
 by Tom Igoe

This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Tone

 */
#include "pitches.h"

// notes in the melody:
int melody[] = {
  //SOL, DO, DO, DO, DO, MI, DO, SOL,0, LA, RE, RE, RE, RE, MI, RE, SOL, 
 //NOTE_DS8, NOTE_D8, NOTE_CS8,NOTE_C8, NOTE_B7, NOTE_AS7, NOTE_A7, NOTE_GS7, NOTE_G7,NOTE_FS7, NOTE_F7,  NOTE_E7, NOTE_DS7, NOTE_D7, NOTE_CS7
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_E5, NOTE_C5, NOTE_F5, NOTE_C6, NOTE_B5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_C5,
  NOTE_D5,NOTE_F5,NOTE_E5,NOTE_D5,NOTE_C5,NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_E5, NOTE_C5, NOTE_F5, NOTE_C6, NOTE_B5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_C5,
  NOTE_D5,NOTE_F5,NOTE_E5,NOTE_D5,NOTE_C5
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  //4,8,8,8,8,8,8,7,8,4,4,4,8,8,8,8,8,8,7,8,2
  3,8,4,4,3,8,2,3,8,4,4,1,3,8,4,4,2,2,3,8,4,4,1,3,8,4,4,3,8,2,3,8,4,4,1,3,8,4,4,2,2,3,8,4,4,1
};

void setup() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 46; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1500 / noteDurations[thisNote];
    tone(13, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(13);
  }
}

void loop() {
}

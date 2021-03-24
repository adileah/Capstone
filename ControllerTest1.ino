 /*********************************************************
Demo of the MPR121 touch sensor and Analog Thumb joystick

ProMicro is detected as an Arduino Leonardo: https://images.app.goo.gl/avKGuAHMM2vES8t7A

**********************************************************/

#include <Wire.h>
#include "Adafruit_MPR121.h"
#include "Joystick.h"

// Create Joystick
Joystick_ Joystick;

// Set to true to test "Auto Send" mode or false to test "Manual Send" mode.
const bool testAutoSendMode = true;

#define X_PIN A1
#define Y_PIN A0
#define SEL_PIN A2

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

void setup() {
  Serial.begin(9600);
  pinMode(SEL_PIN, INPUT_PULLUP);
  
 
  if (testAutoSendMode)
  {
    Joystick.begin();
  }
  else
  {
    Joystick.begin(false);
  }

  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(10);
  }
  
  Serial.println("Adafruit MPR121 Capacitive Touch sensor test"); 
  
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");
  
}
  //////////////////////////////////////////////
  //Buttons Check
  /////////////////////////////////////////////
void loop() {
  // Get the currently touched pads
  currtouched = cap.touched();
  
  for (uint8_t i=0; i<12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      Serial.print(_BV(i)); Serial.print("----"); Serial.println(currtouched);
      Serial.print(i); Serial.println(" touched");
      delay(3000);
      Joystick.setButton(i, 1);
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
     Serial.print(i); Serial.println(" released");
     delay(3000);
     Joystick.setButton(i, 0);
    }
  }
   // reset our state
  lasttouched = currtouched;

  //////////////////////////////////////////////
  //Joystick Check
  /////////////////////////////////////////////
  int x_val = analogRead(X_PIN);
  int y_val = analogRead(Y_PIN);
  int sel_pressed = digitalRead(SEL_PIN);

 Serial.print("X: "); Serial.print(x_val); Serial.print(" Y: "); Serial.print(y_val);
 Serial.print(" Sel: "); Serial.println(sel_pressed);
  Joystick.setXAxis(x_val);
  Joystick.setYAxis(y_val);
  Joystick.setButton(SEL_PIN, sel_pressed);

  ////////////////////////////////////////////
  //send data?
  if (testAutoSendMode == false)
  {
    Joystick.sendState();
  }
  // put a delay so it isn't overwhelming
  delay(10);
}

/*
  Blink the neopixel pin on the Qt Py

  
*/
#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        11
#define NUMPIXELS 1 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

unsigned counter;

// the setup function runs once when you press reset or power the board
void setup() {
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

  // Debugging output
  Serial.begin(9600);
  counter = 0;
}

// the loop function runs over and over again forever
void loop() {
  pixels.clear(); // Set all pixel colors to 'off'

  //pixels.setPixelColor(0, pixels.Color(255 - counter % 255, counter % 255, 0));
  pixels.setPixelColor(0, pixels.Color( random(255), random(255), random(255) ));

  pixels.show();   // Send the updated pixel colors to the hardware.
    
  delay(200);                       // wait for a second
  counter++;
  Serial.printf("no %d\n", counter);
}

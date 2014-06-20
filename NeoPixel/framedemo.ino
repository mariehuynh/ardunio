/*
Marie Huynh
June 20, 2014

This is a frame-based blinky test of NeoPixels driven by an Arduino.
*/

#include <Adafruit_NeoPixel.h>

#define PIN 6       // Your pin may vary
#define N_LEDS 16   // Number of LEDs

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

// You can define more colors, just plug in the RGB values
uint32_t OFF = 0;
uint32_t RED = strip.Color(255,   0,   0);     // Red
uint32_t GRE = strip.Color(  0, 255,   0);     // Green
uint32_t BLU = strip.Color(  0,   0, 255);     // Blue
uint32_t WHI = strip.Color(127, 127, 127); // White

// Remember to change the dimensions below in the loops if you add more rows/frames.
//                       Pixel:     1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16 
uint32_t pattern[10][N_LEDS] = { { WHI, OFF, OFF, WHI, OFF, OFF, WHI, OFF, OFF, GRE, OFF, OFF, GRE, OFF, OFF, GRE },
                                 { OFF, OFF, WHI, OFF, WHI, OFF, OFF, WHI, GRE, OFF, OFF, GRE, OFF, OFF, GRE, OFF },
                                 { OFF, WHI, OFF, OFF, OFF, OFF, WHI, OFF, OFF, OFF, GRE, OFF, OFF, GRE, OFF, OFF },
                                 { OFF, OFF, WHI, OFF, WHI, OFF, OFF, WHI, OFF, GRE, OFF, OFF, GRE, OFF, OFF, GRE },
                                 { WHI, OFF, WHI, OFF, WHI, OFF, WHI, OFF, GRE, OFF, OFF, GRE, OFF, OFF, GRE, OFF },
                                 { OFF, WHI, OFF, WHI, OFF, OFF, OFF, WHI, OFF, OFF, GRE, OFF, OFF, GRE, OFF, OFF },
                                 { WHI, OFF, OFF, OFF, OFF, OFF, WHI, OFF, OFF, GRE, OFF, OFF, GRE, OFF, OFF, GRE },
                                 { OFF, OFF, OFF, WHI, OFF, WHI, OFF, WHI, GRE, OFF, OFF, GRE, OFF, OFF, GRE, OFF },
                                 { OFF, OFF, WHI, OFF, WHI, OFF, WHI, OFF, OFF, OFF, GRE, OFF, OFF, GRE, OFF, OFF },
                                 { OFF, WHI, OFF, OFF, WHI, OFF, OFF, WHI, OFF, GRE, OFF, OFF, GRE, OFF, OFF, GRE }
                               };

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  // Change this to reduce brightness
  strip.setBrightness(255);
}

void loop() {
  blinky(5);
  blinky(10);
  blinky(50);
}

// wait is how long to hold a frame before moving on to the next one. 
void blinky(uint8_t wait) {
  // Go through each of the frames
  for(uint16_t frame = 0; frame < 10; frame++) {
    // Set each pixel in the frame
    for(uint16_t i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, pattern[frame][i]);
    }

    // Display the frame
    strip.show();
    delay(wait);
  }
}
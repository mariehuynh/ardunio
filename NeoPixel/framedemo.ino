/*
Marie Huynh
June 22, 2014

This is a frame-based blinky test of NeoPixels driven by an Arduino.  It compiles to 3,808 bytes, so should fit on Trinkets now.

TODO: Do I need to manually pull strip.Color() out of the loop or will the compiler do that for me because the return value never changes?
*/

#include <Adafruit_NeoPixel.h>

#define PIN 0

// New colors may be added, but need their RGB values defined in the switch below.
// Adhering to three letters is not necessary, but you'll have to fix the spacing and this is already wide.
enum Colors{
  OFF,
  RED,
  GRE,
  BLU,
  YEL,
  WHI,
  WH1,
  WH2,
  WH3,
  TEL,
  TL5
};

  // Each row is a frame.  New rows may be added.
// This takes up much less space than the uint32_t that strip.Color() returns.
//            Pixel:     1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16
int pattern1[][16] = {
                       { WHI, OFF, OFF, WHI, OFF, OFF, GRE, OFF, OFF, RED, OFF, TEL, OFF, OFF, OFF, OFF },
                       { WHI, OFF, WHI, OFF, WHI, OFF, GRE, OFF, GRE, OFF, OFF, TEL, TEL, OFF, OFF, TEL },
                       { WH3, BLU, OFF, OFF, OFF, OFF, GRE, OFF, OFF, YEL, GRE, TEL, TEL, TEL, OFF, OFF },
                       { WH2, OFF, WHI, OFF, WHI, OFF, GRE, OFF, OFF, OFF, OFF, TEL, TEL, TEL, TL5, TEL }
                     };

int pattern2[][16] = {
                       { WH1, OFF, WHI, OFF, OFF, WHI, OFF, RED, BLU, OFF, OFF, TL5, TL5, TL5, OFF, OFF },
                       { OFF, BLU, OFF, WHI, OFF, OFF, OFF, RED, OFF, OFF, BLU, TEL, OFF, OFF, OFF, OFF },
                       { OFF, OFF, OFF, OFF, OFF, OFF, OFF, RED, OFF, GRE, OFF, TEL, TEL, OFF, OFF, TEL },
                       { OFF, OFF, OFF, WHI, OFF, WHI, OFF, RED, RED, OFF, OFF, TL5, TL5, OFF, OFF, OFF },
                     };

int pattern3[][16] = {
                       { WH1, OFF, WHI, OFF, WHI, OFF, GRE, OFF, GRE, OFF, OFF, TEL, TEL, OFF, OFF, OFF },
                       { WH2, BLU, OFF, WHI, OFF, OFF, GRE, OFF, OFF, OFF, RED, TEL, OFF, OFF, OFF, OFF },
                       { WH3, OFF, OFF, OFF, OFF, OFF, GRE, OFF, BLU, RED, OFF, TEL, TEL, OFF, OFF, TEL },
                       { WHI, OFF, OFF, OFF, WHI, OFF, GRE, OFF, OFF, OFF, OFF, TEL, TEL, TEL, OFF, OFF }
                     };

int pattern4[][16] = {
                       { WHI, BLU, OFF, WHI, OFF, OFF, OFF, RED, OFF, OFF, YEL, TEL, TEL, TL5, OFF, TEL },
                       { WHI, OFF, OFF, OFF, OFF, OFF, OFF, RED, OFF, GRE, OFF, TL5, OFF, OFF, OFF, OFF },
                       { WH3, BLU, OFF, WHI, WHI, OFF, OFF, RED, RED, OFF, OFF, TEL, TEL, OFF, OFF, TEL },
                       { WH2, OFF, WHI, OFF, OFF, WHI, OFF, RED, OFF, BLU, GRE, TEL, TEL, TEL, TEL, TEL }
                     };

int pattern5[][16] = {
                       { WH1, BLU, OFF, WHI, OFF, OFF, GRE, OFF, OFF, OFF, OFF, TEL, TEL, TL5, TL5, OFF },
                       { OFF, OFF, OFF, OFF, OFF, OFF, GRE, OFF, OFF, BLU, GRE, TEL, TEL, TEL, OFF, OFF },
                       { OFF, OFF, WHI, OFF, WHI, OFF, GRE, OFF, GRE, OFF, OFF, TEL, TEL, TEL, TEL, TEL },
                       { OFF, BLU, OFF, WHI, OFF, OFF, GRE, OFF, OFF, OFF, RED, TEL, TEL, TL5, TL5, OFF }
                     };

int pattern6[][16] = {
                       { WH1, OFF, OFF, OFF, OFF, OFF, OFF, RED, OFF, GRE, OFF, TEL, TL5, OFF, OFF, TEL },
                       { WH2, OFF, OFF, OFF, OFF, WHI, OFF, RED, BLU, OFF, OFF, TL5, OFF, OFF, OFF, OFF },
                       { WH3, OFF, WHI, OFF, WHI, OFF, OFF, RED, OFF, OFF, GRE, TEL, TEL, OFF, OFF, OFF },
                       { WH1, BLU, OFF, OFF, OFF, WHI, OFF, RED, OFF, RED, OFF, TEL, TL5, OFF, OFF, TEL }
                     };

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  

    // row number to start at, delay
    blinky(pattern1, 20);
    blinky(pattern2, 20);
    blinky(pattern3, 20);
    blinky(pattern4, 20);
    blinky(pattern5, 20);
    blinky(pattern6, 20);

}

void blinky(int pattern[][16], uint8_t wait) {

  uint32_t color;
  // Go through each of the frames
  for(int frame = 0; frame < 4; frame++) {
    // Set each pixel in the frame
    for(int i=0; i < strip.numPixels(); i++) {
      color = strip.Color(255,   0,   0); // default red for debugging

      switch(pattern[frame][i]){
        case OFF:
          color = 0;
          break;
        case RED:
          color = strip.Color(255,   0,   0);
          break;
        case GRE:
          color = strip.Color(  0, 255,   0);
          break;
        case BLU:
          color = strip.Color(  0,   0, 255);
          break;
        case YEL:
          color = strip.Color(255, 255,   0);
          break;
        case WHI:
          color = strip.Color(127, 127, 127);
          break;
        case WH1:
          color = strip.Color( 31,  31,  31);
          break;
        case WH2:
          color = strip.Color( 64,  64,  64);
          break;
        case WH3:
          color = strip.Color( 95,  95,  95);
          break;
        case TEL:
          color = strip.Color(  0, 255, 255);
          break;
        case TL5:
          color = strip.Color(  0,  64,  64);
          break;
      }

      strip.setPixelColor(i, color);
    }

    // Display the frame
    strip.show();

    // Keep that on for some time before moving on to the next frame.
    delay(wait);
  }
}
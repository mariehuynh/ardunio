/*********************************************************************
Marie Huynh

This uses a Monochrome OLED and UV sensor to tell you if you should 
hide from high UV levels.  It also runs on the Gemma M0.

This is based on libraries from Adafruit.  Check them out here:
https://learn.adafruit.com/adafruit-gfx-graphics-library
*********************************************************************/

#include <SPI.h>
#include <Wire.h>

// For Monochrome OLEDs based on SSD1306 drivers
#include <Adafruit_SSD1306.h>

#include <Adafruit_GFX.h>
#include <Fonts/FreeMonoBoldOblique9pt7b.h>

#include "Adafruit_SI1145.h"
Adafruit_SI1145 uv = Adafruit_SI1145();

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

float UVindex;
int toggle = 0;

void setup()   {                

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done
  
  // Clear the buffer.
  display.clearDisplay();
  
  //Font and color
  display.setTextColor(WHITE);
  display.setFont(&FreeMonoBoldOblique9pt7b);
  
  display.setCursor(0,10);
  display.print("Setting up");
  display.display();

  Serial.begin(9600);  
  delay(1000);

  while (! uv.begin()) {
    Serial.println("Didn't find Si1145");
  }
  Serial.println("OK!");
}

void loop() {
  
  // Get UV data
  UVindex = uv.readUV(); 
  UVindex /= 100.0; // the index is multiplied by 100 so to get the integer index, divide by 100!  

  // Move cursor(baseline) back to top left
  display.setCursor(0,10);

  display.print("UV LVL:");
  display.print(UVindex);
  Serial.println(UVindex);

  // Toggle makes it blink
  if (toggle? toggle=0 : toggle=1) {
    if(UVindex < 2) {
      display.println("      Yay!");
    } else {
      display.println("      Hide!");
    }
  }
  
  // Actually write to display
  display.display();
  
  delay(1000);
  
  display.clearDisplay();

}

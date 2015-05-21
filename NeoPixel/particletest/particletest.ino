/******************************************************************************
Marie Huynh
May 12, 2015
Twilio Signal Developer Conference for Communications

This short program attempts to make use of a particle physics library
******************************************************************************/

#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include "RGB.h"

#include "ParticleSys.h"
#include "Particle_Std.h"
#include "Particle_Fixed.h"
#include "Emitter_Fountain.h"
#include "PartMatrix.h"

#define PIN 1

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_TOP    + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);



// For particles setup?

const byte numParticles = 150;
boolean pulseOn = false;

Particle_Std particles[numParticles];
Particle_Fixed source;
Emitter_Fountain emitter(10, 0, 10, &source);
ParticleSys pSys(numParticles, particles, &emitter);
PartMatrix pMatrix;

void setup() {
  
//Debug
Serial.begin(9600);           // set up Serial library at 9600 bps

  matrix.begin();
  matrix.setBrightness(100);

  randomSeed(analogRead(0));
  
   source.vx = 6;
    //source.vy = 10;
    
    source.x = 100;
    source.y = 0;
    Emitter_Fountain::minLife = 1120;
    Emitter_Fountain::maxLife = 1180;
    Particle_Std::ay = 10;
    //PartMatrix::isOverflow = false;

    //init all pixels to zero
    pMatrix.reset();
}

void loop() {
  // Set up blank board

  
  pSys.update();
    drawMatrix();

    delay(80);
}



void drawMatrix(){
    pMatrix.reset();
    pMatrix.render(particles, numParticles);
    //update the actual LED matrix
    for (byte y=0;y<8;y++) {
        for(byte x=0;x<8;x++) {

             matrix.drawPixel(x, y, matrix.Color(pMatrix.matrix[x][y].r, pMatrix.matrix[x][y].g, pMatrix.matrix[x][y].b));

      matrix.show();

        }
    }
}


// Fade pixel (x, y) from startColor to endColor
void fadePixel(int x, int y, RGB startColor, RGB endColor, int steps, int wait) {
  for(int i = 0; i <= steps; i++) 
  {
    int newR = startColor.r + (endColor.r - startColor.r) * i / steps;
    int newG = startColor.g + (endColor.g - startColor.g) * i / steps;
    int newB = startColor.b + (endColor.b - startColor.b) * i / steps;
    
    matrix.drawPixel(x, y, matrix.Color(newR, newG, newB));
    matrix.show();
    delay(wait);
  }
}


/******************************************************************************
Marie Huynh
June 11, 2015

This short program plays Conway's Game of Life on four 8x8 Adafruit NeoMatrices.
******************************************************************************/

#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include "RGB.h"

RGB lowwhite = { 55, 55, 55 };
RGB green = { 0, 255, 0 };
RGB blue = { 0, 0, 255 };


#define PIN 1

int boardwidth = 16;
int boardlength = 16;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, 2, 2, PIN,
  //NEO_MATRIX_TOP    + NEO_MATRIX_LEFT +
  //NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
  NEO_TILE_BOTTOM + NEO_TILE_RIGHT +
  NEO_TILE_COLUMNS + NEO_TILE_ZIGZAG +
  NEO_GRB            + NEO_KHZ800);
  
//Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
//  NEO_MATRIX_TOP    + NEO_MATRIX_LEFT +
//  NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
//  NEO_GRB            + NEO_KHZ800);

// Internal representation of the game
int univ[16][16] = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0},
  {0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0},
  {0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0},
  {0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0},
  {0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0},
  {0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0},
  {0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

int univ1[16][16] = {
  {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};
int next[16][16];


int (*thisboard)[16] = univ;
int (*nextboard)[16] = next;

void setup() {
  matrix.begin();
  matrix.setBrightness(10);

  Serial.begin(9600);

  
  // Generate random board
  randomSeed(analogRead(0));
  for(int i = 0; i < boardwidth; i++){
    for(int j = 0; j < boardlength; j++){
      if (random(0,10) <5)
        univ[i][j] = 1;
      else 
        univ[i][j] = 0;  
    }
  }// Comment this loop out if you want the gliders or pulsar
  
  
  
}


void loop() {
  // Display state
  for(int i = 0; i < boardwidth; i++){
    for(int j = 0; j < boardlength; j++){
      if(thisboard[i][j] == 1)
        matrix.drawPixel(i, j, matrix.Color(blue.r, blue.g, blue.b));

      else if(thisboard[i][j] > 1)
        matrix.drawPixel(i, j, matrix.Color(white.r, white.g, white.b));
      else if(thisboard[i][j] < 1 && nextboard[i][j] > 0)
        matrix.drawPixel(i, j, matrix.Color(255, 0, 0));
        else
        matrix.drawPixel(i, j, matrix.Color(0, 0, 0));
    }
  }
  
  matrix.show();

  // Generate next stage
  for(int i = 0; i < boardwidth; i++){
    for(int j = 0; j < boardlength; j++){
      
      // count neighbors
      int n = 0;
      for(int ii = i-1; ii <= i+1; ii++) {
        for(int jj = j-1; jj <= j+1; jj++) {
          if(thisboard[(ii+boardwidth)%boardwidth][(jj+boardlength)%boardlength])
            n++;          
        }
      }

      // Take out the middle
      if(thisboard[i][j])
        n--;
      if(n == 3 || (n == 2 && thisboard[i][j]))
        nextboard[i][j] = 1 + thisboard[i][j];
      else
        nextboard[i][j] = 0;
    }
  }
  
  // Swap pointers to continue
  int (*temp)[16]   = nextboard;
  nextboard = thisboard;
  thisboard = temp; 
  
    delay(530);
  }

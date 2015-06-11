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


  #define for_x for (int x = 0; x < w; x++)
#define for_y for (int y = 0; y < h; y++)
#define for_xy for_x for_y

void setup() {
  matrix.begin();
  matrix.setBrightness(10);
  //matrix.setTextColor( matrix.Color(white.r, white.g, white.b) );
  //matrix.setTextWrap(false);

  Serial.begin(9600);

  delay(500);
}




void loop() {
  // Display state
  for(int i = 0; i < boardwidth; i++){
    for(int j = 0; j < boardlength; j++){
      if(thisboard[i][j])
        matrix.drawPixel(i, j, matrix.Color(white.r, white.g, white.b));
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
//            Serial.print(i);
//    Serial.print(",");
//    Serial.print(j);
//    Serial.print(":");
//    Serial.println(n);
      // Take out the middle
      if(thisboard[i][j])
        n--;
      nextboard[i][j] = (n == 3 || (n == 2 && thisboard[i][j]));

    }
  }
  
  // Swap pointers to continue
  int (*temp)[16]   = nextboard;
  nextboard = thisboard;
  thisboard = temp; 
  
    delay(20);
  }

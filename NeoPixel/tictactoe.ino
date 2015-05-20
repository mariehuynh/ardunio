#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include "RGB.h"

#define PIN 1

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_TOP    + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

void setup() {
  matrix.begin();
  matrix.setBrightness(20);
  matrix.setTextColor( matrix.Color(white.r, white.g, white.b) );
  matrix.setTextWrap(false);

    Serial.begin(9600);           // set up Serial library at 9600 bps

  
}

int gameboard[3][3] = {
  {0,0,0},
  {0,0,0},
  {0,0,0}
};

void loop() {
  // set up blank board
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      fadePixel(i, j, off, off, 30, 0);
    }
  }
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      gameboard[i][j] = 0;
    }
  }
  
  // Title
  String ttt = "TicTacToe";
  //scrollText(ttt);
  //delay(500);
  
  // Print grid
  drawGrid();
  
  // Play
  int x,y;

  
  // play 9 rounds
  for(int i = 0; i < 9; i++){
    // Pick new spot
    do {
      x = random(0,3);
      y = random(0,3);
    } while (gameboard[x][y] != 0);

    gameboard[x][y] = (i%2) + 1;
    Serial.print("x = ");
    Serial.println(x);    

    Serial.print("y = ");
    Serial.println(y);  

    play(x,y,(i%2)+1); 
  
    // if win, end and display
    if(haswin())
      break;

      //for(uint16_t column=0; column < 3; column++) {    

    


    delay(500);

  }
}

int haswin() {
  int win = 0;
  for(uint16_t i=0; i < 3; i++) {
    if(gameboard[i][0] > 0 && 
      gameboard[i][0] == gameboard[i][1] && 
      gameboard[i][0] == gameboard[i][2]) {
        displaywin(gameboard[i][0]);
        return 1;
    } else if(gameboard[0][i] > 0 && 
      gameboard[0][i] == gameboard[1][i] && 
      gameboard[0][i] == gameboard[2][i]) {
        displaywin(gameboard[0][i]);
        return 1; 
    }else if(gameboard[0][0] > 0 && 
      gameboard[0][0] == gameboard[1][1] && 
      gameboard[0][0] == gameboard[2][2]) {
        displaywin(gameboard[0][0]);
        return 1; 
    }else if(gameboard[0][2] > 0 && 
      gameboard[0][2] == gameboard[1][1] && 
      gameboard[1][1] == gameboard[2][0]) {
        displaywin(gameboard[0][0]);
        return 1; 
    }
  }
  return 0;
}

void displaywin(int winner){
  String winnertext = "Win!";
  scrollText(winnertext);
}
//draw grid
void drawGrid(){
  // This 8x8 array represents the LED matrix pixels. 
  // A value of 1 means we’ll fade the pixel to white
  int logo[8][8] = {  
   {0, 0, 1, 0, 0, 1, 0, 0},
   {0, 0, 1, 0, 0, 1, 0, 0},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {0, 0, 1, 0, 0, 1, 0, 0},
   {0, 0, 1, 0, 0, 1, 0, 0},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {0, 0, 1, 0, 0, 1, 0, 0},
   {0, 0, 1, 0, 0, 1, 0, 0}

  };
   
  for(int row = 0; row < 8; row++) {
    for(int column = 0; column < 8; column++) {
      if(logo[row][column] == 1) {
        fadePixel(column, row, purple, white, 30, 0);
      }
    }
  } 
  
}

//draw grid
void play(int x, int y, int player){
    Serial.print("player = ");
    Serial.println(player);  
   
  for(int row = x*3; row < (x*3)+2; row++) {
    for(int column = y*3; column < (y*3)+2; column++) {

    Serial.print("row = ");
    Serial.println(row);  
    Serial.print("col = ");
    Serial.println(column);  

      if(player < 2) {
        fadePixel(column, row, off, teal, 30, 0);
      }else{
        fadePixel(column, row, off, orange, 30, 0);
      }

    }
  }
} 





// Fill the dots one after the other with a color
void animation(RGB color, uint8_t wait) {
  for(uint16_t row=0; row < 8; row++) {
    for(uint16_t column=0; column < 8; column++) {
      matrix.drawPixel(column, row, matrix.Color(color.r, color.g, color.b));
      matrix.show();
      delay(wait);
    }
  }
}


// Fill the dots one after the other with a color
void colorWipe(RGB color, uint8_t wait) {
  for(uint16_t row=0; row < 8; row++) {
    for(uint16_t column=0; column < 8; column++) {
      matrix.drawPixel(column, row, matrix.Color(color.r, color.g, color.b));
      matrix.show();
      delay(wait);
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

// Crossfade entire screen from startColor to endColor
void crossFade(RGB startColor, RGB endColor, int steps, int wait) {
  for(int i = 0; i <= steps; i++)
  {
     int newR = startColor.r + (endColor.r - startColor.r) * i / steps;
     int newG = startColor.g + (endColor.g - startColor.g) * i / steps;
     int newB = startColor.b + (endColor.b - startColor.b) * i / steps;
     
     matrix.fillScreen(matrix.Color(newR, newG, newB));
     matrix.show();
     delay(wait);
  }
}

void scrollText(String textToDisplay) {
  int x = matrix.width();
  int pixelsInText = textToDisplay.length() * 7;
  
  matrix.setCursor(x, 0);
  matrix.print(textToDisplay);
  matrix.show();
  
  while(x > (matrix.width() - pixelsInText)) {
    matrix.fillScreen(matrix.Color(teal.r, teal.g, teal.b));
    matrix.setCursor(--x, 0);
    matrix.print(textToDisplay);
    matrix.show();
    delay(150);
  }
}



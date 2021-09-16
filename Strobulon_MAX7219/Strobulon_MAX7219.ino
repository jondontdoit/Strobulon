//We always have to include the library
#include "LedControl.h"

/*
 ******************************************
 STROBE HELMET - Main
 ******************************************
 Pin 12 is connected to the DataIn [BLUE]
 Pin 11 is connected to the CLK   [GREEN]
 Pin 10 is connected to LOAD     [YELLOW]
 4x LED grids (8x8)
 ******************************************
 STROBE EYES AND BOTTOM ROW - Misc
 ******************************************
 Pin  7 is connected to the DataIn [BLUE]
 Pin  6 is connected to the CLK   [GREEN]
 Pin  5 is connected to LOAD     [YELLOW]
 BOTTOM are rows 0-3
 EYES are rows 4-7
*/
LedControl lc_main = LedControl(12,11,10,4);
LedControl lc_misc = LedControl( 7, 6, 5,1);

void setup() {

  //Configure debug pin
  pinMode(LED_BUILTIN, OUTPUT);  
  
  //Initialize Strobe Helmet
  for(int i=0; i<1; i++) {
    lc_main.shutdown(i,false);
    lc_main.setIntensity(i,15);
    lc_main.clearDisplay(i);
  }
  
  //Initialize eyes and bottom row
  lc_misc.shutdown(0,false);
  lc_misc.setIntensity(0,15);
  lc_misc.clearDisplay(0);

  allOff();
  //eyesOn();
  //Serial.begin(9600);

  randomSeed(analogRead(0));
}

void loop() {
//  int i = 0;
//  int r = random(18);

  // LIGHT TEST Alternating on and off
  allOn();
  delay(2000);
  allOff();
  delay(1000);

/*
  //allOff();
  //allOn();
  //delay(1000);
  //eyesSad();
  maskOff();
  //eyesOn();
  //delay(1000);
  //eyesHappy();
  //delay(1000);
  //eyesSad();
  //delay(1000);
  //aniFadeOut();
  //eyesAngry();
  eyesOn();
  //aniFadeIn();
  //delay(2000);
  //eyesOn();

  if (r == 0) {
  
  //Rows fill up
  //maskOff();
  for (i=0;i<9;i++) {
     setRow(i);
     delay(100);
  }

  } else if (r == 1) {

  //Alternating rows on and off
  for (i=0;i<8;i++) {
     rowsOn(0);
     delay(100);
     rowsOn(1);
     delay(100);
  }

  } else if (r == 2) {
  
  //Thin diamonds moving left
  for (i=0; i<6; i++) {
    aniArgyleLt();
  }  

  } else if (r == 3) {

  //Fade Intensity in and out
  allOn();
  //delay(1000);
  for (i=0; i<2; i++) {
    aniFadeIn();
    aniFadeOut();
  }
  aniFadeIn();

  } else if (r == 4) {

  //Chevron up
  for (i=0; i<12; i++) {
    aniArrUp();
  }

  } else if (r == 5) {

  //Fast rows up
  for (i=0; i<4; i++) {
    aniRowsUp();
  }

  } else if (r == 6) {

  //Fast rows down
  for (i=0; i<4; i++) {
    aniRowsDn();
  }

  } else if (r == 7) {

  //Fast cols left and right
  for (i=0; i<2; i++) {
    aniColsLt();
    aniColsRt();
  }  

  } else if (r == 8) {

  //Chevrons moving left
  for (i=0; i<12; i++) {
    aniChevLt();
  }  

  } else if (r == 9) {
  
  //Cols fill up
  maskOff();
  for (i=0;i<32;i++) {
     setCol(i);
     delay(50);
  }

  } else if (r == 10) {

  //Alternating cols on and off
  for (i=0;i<8;i++) {
     colsOn(0);
     delay(100);
     colsOn(1);
     delay(100);
  }

  } else if (r == 11) {

  //Rounds up
  for (i=0; i<12; i++) {
    aniRndUp();
  }

  } else if (r == 12) {

  //Fast cols left
  for (i=0; i<2; i++) {
    aniColsLt();
  }

  } else if (r == 13) {
  
  //Fast cols right
  for (i=0; i<2; i++) {
    aniColsRt();
  }

  } else if (r == 14) {
  
  //Fast rows up and down
  for (i=0; i<4; i++) {
    aniRowsUp();
    aniRowsDn();
  }

  } else if (r == 15) {
    
  //Strobe  
  for (i=0; i<6; i++) {
    allOn();
    delay(50);
    maskOff();
    delay(800);
  }

  } else if (r == 16) {
  
  //Thick diamonds moving right
  for (i=0; i<6; i++) {
    aniArgyleRt();
  }  

  } else {
  
  //Random LEDs
  for (i=0; i<16; i++) {
    aniRndLed();
  }

  }
*/
}

/***************************************
 * Static Displays
 ***************************************/

void allOn() {
  /* turn on all LEDs */
  digitalWrite(LED_BUILTIN, LOW);
  
  //Main
  for (int a=0; a<4; a++) {
    for (int i=0; i<8; i++) {
      lc_main.setRow(a,i,B11111111);
    }
  }
  //Misc
  for (int i=0; i<8; i++) {
    lc_misc.setRow(0,i,B11111111);
  }
  
  digitalWrite(LED_BUILTIN, HIGH);
}

void allOff() {
  /* turn off all LEDs */
  digitalWrite(LED_BUILTIN, LOW);
  
  //Main
  for (int a=0; a<4; a++) {
    for (int i=0; i<8; i++) {
      lc_main.setRow(a,i,B00000000);
    }
  }
  //Misc
  for (int i=0; i<8; i++) {
    lc_misc.setRow(0,i,B00000000);
  }
  
  digitalWrite(LED_BUILTIN, HIGH);
}

void maskOff() {
  /* turn off all LEDs */
  int i = 0;
  int n = 0;
  int address = 0;
  for (i=0;i<32;i++) {
    if (n == 8) { address++; n=0; }
    lc_main.setRow(address,n,B00000000);
    n++;
  }
  //Misc
  for (i=0;i<4;i++) {
    lc_misc.setRow(0,i,B00000000);
  }
}

void eyesOn() {
  /* turn on all LEDs */
  int i = 0;
  //Misc
  for (i=5;i<8;i++) {
    lc_misc.setRow(0,i,B11111111);
  }
}

void eyesOff() {
  /* turn off all LEDs */
  int i = 0;
  //Misc
  for (i=5;i<8;i++) {
    lc_misc.setRow(0,i,B00000000);
  }
}

void eyesAngry() {
  //Misc
  lc_misc.setRow(0,5,B00011000);
  lc_misc.setRow(0,6,B00011000);
  lc_misc.setRow(0,7,B11111111);
}

void eyesHappy() {
  //Misc
  lc_misc.setRow(0,5,B10011001);
  lc_misc.setRow(0,6,B10011001);
  lc_misc.setRow(0,7,B11111111);
}

void eyesSad() {
  //Misc
  lc_misc.setRow(0,5,B11111111);
  lc_misc.setRow(0,6,B10011001);
  lc_misc.setRow(0,7,B10011001);
}

void setRow(char row = 0) {
  /* turn on a row of LEDs */
  if (row < 8) {
    lc_main.setRow(0,7-row,B11111111);
    lc_main.setRow(1,7-row,B11111111);
    lc_main.setRow(2,7-row,B11111111);
    lc_main.setRow(3,7-row,B11111111);    
  } else if (row == 8) {
    lc_misc.setRow(0,0,B11111111);
    lc_misc.setRow(0,1,B11111111);
    lc_misc.setRow(0,2,B11111111);
    lc_misc.setRow(0,3,B11111111);  
  }
}

void rowsOn(char odd = 0) {
  /* turn on alternating rows */
  maskOff();
  for (int i=odd; i<9; i+=2) {
    setRow(i);
  }
}

void setCol(char col = 0) {
  /* turn on a column of LEDs */
  char column = col % 8;
  char address = 0;
  if (col < 8) { 
    address = 0; 
  } else if (col < 16) {
    address = 1;
  } else if (col < 24) {
    address = 2;
  } else if (col < 32) {
    address = 3;
  }
  lc_main.setColumn(address,7-column,B11111111);
  //lc_misc.setRow(0,address,1<<col);
  lc_misc.setLed(0,address,7-column,1);
}

void colsOn(char odd = 0) {
  /* turn on alternating columns */
  maskOff();
  for (int i=odd; i<32; i+=2) {
    setCol(i);
  }
}


/***************************************
 * Dynamic Displays
 ***************************************/
void aniRowsUp() {
  for (int i=0;i<9;i++) {   
    maskOff();
    setRow(i);
  }
}
void aniRowsDn() {
  for (int i=0;i<9;i++) {   
    maskOff();
    setRow(9-i);
  }
}
void aniColsLt() {
  for (int i=0;i<32;i++) {   
    maskOff();
    setCol(32-i);
  } 
}
void aniColsRt() {
  for (int i=0;i<32;i++) {   
    maskOff();
    setCol(i);
  } 
}
void aniFadeIn() {
  for (int n=0;n<16;n++) {
    lc_main.setIntensity(0,n);
    lc_main.setIntensity(1,n);
    lc_main.setIntensity(2,n);
    lc_main.setIntensity(3,n);
    lc_misc.setIntensity(0,n);
    delay(50);
  }  
}
void aniFadeOut() {
  for (int n=0;n<16;n++) {
    lc_main.setIntensity(0,15-n);
    lc_main.setIntensity(1,15-n);
    lc_main.setIntensity(2,15-n);
    lc_main.setIntensity(3,15-n);
    lc_misc.setIntensity(0,15-n);
    delay(50);
  }  
}
void aniRndLed() {
  maskOff();
  for (int i=0;i<4;i++) {
    lc_main.setLed(i,random(8),random(8),1);
    lc_main.setLed(i,random(8),random(8),1);
    lc_main.setLed(i,random(8),random(8),1);
    lc_main.setLed(i,random(8),random(8),1);
    lc_main.setLed(i,random(8),random(8),1);
    lc_main.setLed(i,random(8),random(8),1);
    lc_main.setLed(i,random(8),random(8),1);
    lc_main.setLed(i,random(8),random(8),1);
    lc_main.setLed(i,random(8),random(8),1);
    lc_main.setLed(i,random(8),random(8),1);
    lc_main.setLed(i,random(8),random(8),1);
    lc_main.setLed(i,random(8),random(8),1);
    lc_main.setLed(i,random(8),random(8),1);
    lc_main.setLed(i,random(8),random(8),1);
    lc_main.setLed(i,random(8),random(8),1);
    lc_main.setLed(i,random(8),random(8),1);
    lc_misc.setLed(0,i,random(8),1);
    lc_misc.setLed(0,i,random(8),1);
    lc_misc.setLed(0,i,random(8),1);
    lc_misc.setLed(0,i,random(8),1);
    delay(50);
  }  
}
void aniChevLt() {
  int i = 0;
  for (i=0; i<4; i++) {
    lc_main.setRow(i,7,B11001100);
    lc_main.setRow(i,6,B01100110);
    lc_main.setRow(i,5,B00110011);
    lc_main.setRow(i,4,B10011001);
    lc_main.setRow(i,3,B11001100);
    lc_main.setRow(i,2,B10011001);
    lc_main.setRow(i,1,B00110011);
    lc_main.setRow(i,0,B01100110);
    lc_misc.setRow(0,i,B11001100);
  }
  delay(100);
  for (i=0; i<4; i++) {
    lc_main.setRow(i,7,B01100110);
    lc_main.setRow(i,6,B00110011);
    lc_main.setRow(i,5,B10011001);
    lc_main.setRow(i,4,B11001100);
    lc_main.setRow(i,3,B01100110);
    lc_main.setRow(i,2,B11001100);
    lc_main.setRow(i,1,B10011001);
    lc_main.setRow(i,0,B00110011);
    lc_misc.setRow(0,i,B01100110);
  }
  delay(100);
  for (i=0; i<4; i++) {
    lc_main.setRow(i,7,B00110011);
    lc_main.setRow(i,6,B10011001);
    lc_main.setRow(i,5,B11001100);
    lc_main.setRow(i,4,B01100110);
    lc_main.setRow(i,3,B00110011);
    lc_main.setRow(i,2,B01100110);
    lc_main.setRow(i,1,B11001100);
    lc_main.setRow(i,0,B10011001);
    lc_misc.setRow(0,i,B00110011);
  }
  delay(100);
  for (i=0; i<4; i++) {
    lc_main.setRow(i,7,B10011001);
    lc_main.setRow(i,6,B11001100);
    lc_main.setRow(i,5,B01100110);
    lc_main.setRow(i,4,B00110011);
    lc_main.setRow(i,3,B10011001);
    lc_main.setRow(i,2,B00110011);
    lc_main.setRow(i,1,B01100110);
    lc_main.setRow(i,0,B11001100);
    lc_misc.setRow(0,i,B10011001);
  }
  delay(100);
}
void aniArgyleLt() {
  int i = 0;
  for (i=0; i<4; i++) {
    lc_main.setRow(i,7,B10000001);
    lc_main.setRow(i,6,B01000010);
    lc_main.setRow(i,5,B00100100);
    lc_main.setRow(i,4,B00011000);
    lc_main.setRow(i,3,B00000000);
    lc_main.setRow(i,2,B00011000);
    lc_main.setRow(i,1,B00100100);
    lc_main.setRow(i,0,B01000010);
    lc_misc.setRow(0,i,B10000001);
  }
  delay(100);
  for (i=0; i<4; i++) {
    lc_main.setRow(i,7,B11000000);
    lc_main.setRow(i,6,B00100001);
    lc_main.setRow(i,5,B00010010);
    lc_main.setRow(i,4,B00001100);
    lc_main.setRow(i,3,B00000000);
    lc_main.setRow(i,2,B00001100);
    lc_main.setRow(i,1,B00010010);
    lc_main.setRow(i,0,B00100001);
    lc_misc.setRow(0,i,B11000000);
  }
  delay(100);
  for (i=0; i<4; i++) {
    lc_main.setRow(i,7,B01100000);
    lc_main.setRow(i,6,B10010000);
    lc_main.setRow(i,5,B00001001);
    lc_main.setRow(i,4,B00000110);
    lc_main.setRow(i,3,B00000000);
    lc_main.setRow(i,2,B00000110);
    lc_main.setRow(i,1,B00001001);
    lc_main.setRow(i,0,B10010000);
    lc_misc.setRow(0,i,B01100000);
  }
  delay(100);
  for (i=0; i<4; i++) {
    lc_main.setRow(i,7,B00110000);
    lc_main.setRow(i,6,B01001000);
    lc_main.setRow(i,5,B10000100);
    lc_main.setRow(i,4,B00000011);
    lc_main.setRow(i,3,B00000000);
    lc_main.setRow(i,2,B00000011);
    lc_main.setRow(i,1,B10000100);
    lc_main.setRow(i,0,B01001000);
    lc_misc.setRow(0,i,B00110000);
  }
  delay(100);
  for (i=0; i<4; i++) {
    lc_main.setRow(i,7,B00011000);
    lc_main.setRow(i,6,B00100100);
    lc_main.setRow(i,5,B01000010);
    lc_main.setRow(i,4,B10000001);
    lc_main.setRow(i,3,B00000000);
    lc_main.setRow(i,2,B10000001);
    lc_main.setRow(i,1,B01000010);
    lc_main.setRow(i,0,B00100100);
    lc_misc.setRow(0,i,B00011000);
  }
  delay(100);
  for (i=0; i<4; i++) {
    lc_main.setRow(i,7,B00001100);
    lc_main.setRow(i,6,B00010010);
    lc_main.setRow(i,5,B00100001);
    lc_main.setRow(i,4,B11000000);
    lc_main.setRow(i,3,B00000000);
    lc_main.setRow(i,2,B11000000);
    lc_main.setRow(i,1,B00100001);
    lc_main.setRow(i,0,B00010010);
    lc_misc.setRow(0,i,B00001100);
  }
  delay(100);
  for (i=0; i<4; i++) {
    lc_main.setRow(i,7,B00000110);
    lc_main.setRow(i,6,B00001001);
    lc_main.setRow(i,5,B10010000);
    lc_main.setRow(i,4,B01100000);
    lc_main.setRow(i,3,B00000000);
    lc_main.setRow(i,2,B01100000);
    lc_main.setRow(i,1,B10010000);
    lc_main.setRow(i,0,B00001001);
    lc_misc.setRow(0,i,B00000110);
  }
  delay(100);
  for (i=0; i<4; i++) {
    lc_main.setRow(i,7,B00000011);
    lc_main.setRow(i,6,B10000100);
    lc_main.setRow(i,5,B01001000);
    lc_main.setRow(i,4,B00110000);
    lc_main.setRow(i,3,B00000000);
    lc_main.setRow(i,2,B00110000);
    lc_main.setRow(i,1,B01001000);
    lc_main.setRow(i,0,B10000100);
    lc_misc.setRow(0,i,B00000011);
  }
  delay(100);
}
void aniArgyleRt() {
  int i = 0;
  for (i=0; i<4; i++) {
    lc_main.setRow(i,7,B10000001);
    lc_main.setRow(i,6,B11000011);
    lc_main.setRow(i,5,B01100110);
    lc_main.setRow(i,4,B00111100);
    lc_main.setRow(i,3,B00011000);
    lc_main.setRow(i,2,B00111100);
    lc_main.setRow(i,1,B01100110);
    lc_main.setRow(i,0,B11000011);
    lc_misc.setRow(0,i,B10000001);
  }
  delay(100);
  for (i=0; i<4; i++) {
    lc_main.setRow(i,7,B00000011);
    lc_main.setRow(i,6,B10000111);
    lc_main.setRow(i,5,B11001100);
    lc_main.setRow(i,4,B01111000);
    lc_main.setRow(i,3,B00110000);
    lc_main.setRow(i,2,B01111000);
    lc_main.setRow(i,1,B11001100);
    lc_main.setRow(i,0,B10000111);
    lc_misc.setRow(0,i,B00000011);
  }
  delay(100);
  for (i=0; i<4; i++) {
    lc_main.setRow(i,7,B00000110);
    lc_main.setRow(i,6,B00001111);
    lc_main.setRow(i,5,B10011001);
    lc_main.setRow(i,4,B11110000);
    lc_main.setRow(i,3,B01100000);
    lc_main.setRow(i,2,B11110000);
    lc_main.setRow(i,1,B10011001);
    lc_main.setRow(i,0,B00001111);
    lc_misc.setRow(0,i,B00000110);
  }
  delay(100);
  for (i=0; i<4; i++) {
    lc_main.setRow(i,7,B00001100);
    lc_main.setRow(i,6,B00011110);
    lc_main.setRow(i,5,B00110011);
    lc_main.setRow(i,4,B11100001);
    lc_main.setRow(i,3,B11000000);
    lc_main.setRow(i,2,B11100001);
    lc_main.setRow(i,1,B00110011);
    lc_main.setRow(i,0,B00011110);
    lc_misc.setRow(0,i,B00001100);
  }
  delay(100);
  for (i=0; i<4; i++) {
    lc_main.setRow(i,7,B00011000);
    lc_main.setRow(i,6,B00111100);
    lc_main.setRow(i,5,B01100110);
    lc_main.setRow(i,4,B11000011);
    lc_main.setRow(i,3,B10000001);
    lc_main.setRow(i,2,B11000011);
    lc_main.setRow(i,1,B01100110);
    lc_main.setRow(i,0,B00111100);
    lc_misc.setRow(0,i,B00011000);
  }
  delay(100);
  for (i=0; i<4; i++) {
    lc_main.setRow(i,7,B00110000);
    lc_main.setRow(i,6,B01111000);
    lc_main.setRow(i,5,B11001100);
    lc_main.setRow(i,4,B10000111);
    lc_main.setRow(i,3,B00000011);
    lc_main.setRow(i,2,B10000111);
    lc_main.setRow(i,1,B11001100);
    lc_main.setRow(i,0,B01111000);
    lc_misc.setRow(0,i,B00110000);
  }
  delay(100);
  for (i=0; i<4; i++) {
    lc_main.setRow(i,7,B01100000);
    lc_main.setRow(i,6,B11110000);
    lc_main.setRow(i,5,B10011001);
    lc_main.setRow(i,4,B00001111);
    lc_main.setRow(i,3,B00000110);
    lc_main.setRow(i,2,B00001111);
    lc_main.setRow(i,1,B10011001);
    lc_main.setRow(i,0,B11110000);
    lc_misc.setRow(0,i,B01100000);
  }
  delay(100);
  for (i=0; i<4; i++) {
    lc_main.setRow(i,7,B11000000);
    lc_main.setRow(i,6,B11100001);
    lc_main.setRow(i,5,B00110011);
    lc_main.setRow(i,4,B00011110);
    lc_main.setRow(i,3,B00001100);
    lc_main.setRow(i,2,B00011110);
    lc_main.setRow(i,1,B00110011);
    lc_main.setRow(i,0,B11100001);
    lc_misc.setRow(0,i,B11000000);
  }
  delay(100);
}
void aniRndUp() {
  int i = 0;
  for (i=0; i<4; i++) {
    lc_main.setRow(i,7,B00011000);
    lc_main.setRow(i,6,B01100110);
    lc_main.setRow(i,5,B10000001);
    lc_main.setRow(i,4,B00000000);
    lc_main.setRow(i,3,B00011000);
    lc_main.setRow(i,2,B01100110);
    lc_main.setRow(i,1,B10000001);
    lc_main.setRow(i,0,B00000000);
    lc_misc.setRow(0,i,B00011000);
  }
  delay(100);
  for (i=0; i<4; i++) {
    lc_main.setRow(i,7,B01100110);
    lc_main.setRow(i,6,B10000001);
    lc_main.setRow(i,5,B00000000);
    lc_main.setRow(i,4,B00011000);
    lc_main.setRow(i,3,B01100110);
    lc_main.setRow(i,2,B10000001);
    lc_main.setRow(i,1,B00000000);
    lc_main.setRow(i,0,B00011000);
    lc_misc.setRow(0,i,B01100110);
  }
  delay(100);
  for (i=0; i<4; i++) {
    lc_main.setRow(i,7,B10000001);
    lc_main.setRow(i,6,B00000000);
    lc_main.setRow(i,5,B00011000);
    lc_main.setRow(i,4,B01100110);
    lc_main.setRow(i,3,B10000001);
    lc_main.setRow(i,2,B00000000);
    lc_main.setRow(i,1,B00011000);
    lc_main.setRow(i,0,B01100110);
    lc_misc.setRow(0,i,B10000001);
  }
  delay(100);
  for (i=0; i<4; i++) {
    lc_main.setRow(i,7,B00000000);
    lc_main.setRow(i,6,B00011000);
    lc_main.setRow(i,5,B01100110);
    lc_main.setRow(i,4,B10000001);
    lc_main.setRow(i,3,B00000000);
    lc_main.setRow(i,2,B00011000);
    lc_main.setRow(i,1,B01100110);
    lc_main.setRow(i,0,B10000001);
    lc_misc.setRow(0,i,B00000000);
  }
  delay(100);
}
void aniArrUp() {
  int i = 0;
  for (i=0; i<4; i++) {
    lc_main.setRow(i,7,B00011000);
    lc_main.setRow(i,6,B00111100);
    lc_main.setRow(i,5,B01100110);
    lc_main.setRow(i,4,B11000011);
    lc_main.setRow(i,3,B10000001);
    lc_main.setRow(i,2,B00011000);
    lc_main.setRow(i,1,B00111100);
    lc_main.setRow(i,0,B01100110);
    lc_misc.setRow(0,i,B11000011);
  }
  delay(100);
  for (i=0; i<4; i++) {
    lc_main.setRow(i,7,B00111100);
    lc_main.setRow(i,6,B01100110);
    lc_main.setRow(i,5,B11000011);
    lc_main.setRow(i,4,B10000001);
    lc_main.setRow(i,3,B00011000);
    lc_main.setRow(i,2,B00111100);
    lc_main.setRow(i,1,B01100110);
    lc_main.setRow(i,0,B11000011);
    lc_misc.setRow(0,i,B10000001);
  }
  delay(100);
  for (i=0; i<4; i++) {
    lc_main.setRow(i,7,B01100110);
    lc_main.setRow(i,6,B11000011);
    lc_main.setRow(i,5,B10000001);
    lc_main.setRow(i,4,B00011000);
    lc_main.setRow(i,3,B00111100);
    lc_main.setRow(i,2,B01100110);
    lc_main.setRow(i,1,B11000011);
    lc_main.setRow(i,0,B10000001);
    lc_misc.setRow(0,i,B00011000);
  }
  delay(100);
  for (i=0; i<4; i++) {
    lc_main.setRow(i,7,B11000011);
    lc_main.setRow(i,6,B10000001);
    lc_main.setRow(i,5,B00011000);
    lc_main.setRow(i,4,B00111100);
    lc_main.setRow(i,3,B01100110);
    lc_main.setRow(i,2,B11000011);
    lc_main.setRow(i,1,B10000001);
    lc_main.setRow(i,0,B00011000);
    lc_misc.setRow(0,i,B00111100);
  }
  delay(100);
  for (i=0; i<4; i++) {
    lc_main.setRow(i,7,B10000001);
    lc_main.setRow(i,6,B00011000);
    lc_main.setRow(i,5,B00111100);
    lc_main.setRow(i,4,B01100110);
    lc_main.setRow(i,3,B11000011);
    lc_main.setRow(i,2,B10000001);
    lc_main.setRow(i,1,B00011000);
    lc_main.setRow(i,0,B00111100);
    lc_misc.setRow(0,i,B01100110);
  }
  delay(100);
}

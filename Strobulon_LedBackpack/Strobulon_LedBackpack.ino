#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include "animations.h"

Adafruit_8x16matrix matrix[2] = {Adafruit_8x16matrix(), Adafruit_8x16matrix()};
Adafruit_8x16matrix matrixrow = Adafruit_8x16matrix();

byte toggle = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);  
  pinMode(1, OUTPUT);
  
  matrix[0].begin(0x70);
  matrix[1].begin(0x71);
  matrixrow.begin(0x73);

  allOff();
  delay(500);
  allOn();
  delay(500);
  allOff();

  randomSeed(analogRead(A3));
}

void loop() {

  int a = 0, n = 0;
  
  miscOn();

  switch (random(10)) {
    
    // Fill in columns
    case 1:
      allOff();
      delay(50);
      
      for (int i=0; i<32; i++) {
        a = i/16;
        n = i%16;
        
        matrix[a].drawLine(0,n, 7,n, LED_ON);
        matrix[a].writeDisplay();  // write the changes we just made to the display
    
        btmRowSet(i);
        matrixrow.writeDisplay();
    
        digitalWrite(1,toggle);
        toggle = !toggle;
        
        delay(50);
      }      
      break;
    
    // Fill in rows
    case 2:
      allOff();
      delay(50);

      btmRowOn();
      matrixrow.writeDisplay();
      delay(50);
      
      for (int i=0; i<8; i++) {
        n = 7-i;
        
        matrix[0].drawLine(n,0, n,15, LED_ON);
        matrix[1].drawLine(n,0, n,15, LED_ON);
        
        matrix[0].writeDisplay();  // write the changes we just made to the display
        matrix[1].writeDisplay();  // write the changes we just made to the display
        
        delay(50);
      }      
      break;

    // Fast bouncing rows
    case 3:
      
      // Loop 5 times
      for (int l=0; l<5; l++) {
        
        for (int i=0; i<8; i++) {
          n = i;
          
          matrix[0].clear();
          matrix[1].clear();
          
          matrix[0].drawLine(n,0, n,15, LED_ON);
          matrix[1].drawLine(n,0, n,15, LED_ON);
          
          matrix[0].writeDisplay();  // write the changes we just made to the display
          matrix[1].writeDisplay();  // write the changes we just made to the display
          
          delay(20);
        }    

        btmRowOn();
        matrixrow.writeDisplay();
        delay(20);
        btmRowOff();
        matrixrow.writeDisplay();
        
        for (int i=0; i<8; i++) {
          n = 7-i;
          
          matrix[0].clear();
          matrix[1].clear();
          
          matrix[0].drawLine(n,0, n,15, LED_ON);
          matrix[1].drawLine(n,0, n,15, LED_ON);
          
          matrix[0].writeDisplay();  // write the changes we just made to the display
          matrix[1].writeDisplay();  // write the changes we just made to the display
          
          delay(20);
        }
      }
      break;
      
    // Fast bouncing columns
    case 4:
      miscOn();
      // Loop 5 times
      for (int l=0; l<5; l++) {
        for (int i=0; i<16; i++) {
          n = i;
          
          matrix[0].clear();
          matrix[1].clear();
          btmRowOff();
          
          matrix[0].drawLine(0,n, 7,n, LED_ON);
          matrix[1].drawLine(0,(15-n), 7,(15-n), LED_ON);
          
          matrix[0].writeDisplay();  // write the changes we just made to the display
          matrix[1].writeDisplay();  // write the changes we just made to the display

          btmRowSet(n);
          btmRowSet(31-n);
          matrixrow.writeDisplay();
          
          delay(20);
        }   
        for (int i=0; i<16; i++) {
          n = 15-i;
          
          matrix[0].clear();
          matrix[1].clear();
          btmRowOff();
          
          matrix[0].drawLine(0,n, 7,n, LED_ON);
          matrix[1].drawLine(0,(15-n), 7,(15-n), LED_ON);
          
          matrix[0].writeDisplay();  // write the changes we just made to the display
          matrix[1].writeDisplay();  // write the changes we just made to the display
          
          btmRowSet(n);
          btmRowSet(31-n);
          matrixrow.writeDisplay();
          
          delay(20);
        }    
      }
      break;
      
    // Fast shooting rows
    case 5:
      miscOn();
      // Loop 10 times
      for (int l=0; l<10; l++) {
        for (int i=0; i<8; i++) {
          n = 7-i;
          
          matrix[0].clear();
          matrix[1].clear();
          
          matrix[0].drawLine(n,0, n,15, LED_ON);
          matrix[1].drawLine(n,0, n,15, LED_ON);
          
          matrix[0].writeDisplay();  // write the changes we just made to the display
          matrix[1].writeDisplay();  // write the changes we just made to the display
          
          delay(20);
        }
        
        btmRowOn();
        matrixrow.writeDisplay();
        delay(20);
        btmRowOff();
        matrixrow.writeDisplay();
      }
      break;
      
    // Strobe
    case 6:
      // Loop 50 times
      for (int l=0; l<50; l++) {
        allOn();
        delay(30);
        allOff();
        delay(30);
      }
      break;
      
    // Strobe-Flash
    case 7:
      // Loop 3 times
      for (int l=0; l<3; l++) {
        allOn();
        delay(50);
        allOff();
        delay(1000);
      }
      break;
      
    // Noise
    case 8:
      matrix[0].clear();
      matrix[1].clear();
      btmRowOff();
      
      // Loop 500 times
      for (int l=0; l<500; l++) {

        int i = random(9*32);
        if (i < 32) {
          btmRowSet(i);
          matrixrow.writeDisplay();
        } else {
          matrix[random(2)].drawPixel(random(8), random(16), LED_ON);
          matrix[0].writeDisplay();  // write the changes we just made to the display
          matrix[1].writeDisplay();  // write the changes we just made to the display
          delay(5);
        }
      }
      break;
      
    // Eyes
    case 9:
      allOn();
      
      // Loop 5 times
      for (int l=0; l<8; l++) {
        for (int i=0; i<10; i++) {
          eyesSet(i);
          matrixrow.writeDisplay();
          delay(30);
          eyesOff();
          matrixrow.writeDisplay();
        }
      }
      break;

    // Else, just turn it all on
    default:
      allOn();
      delay(100);
      break;
  }
  


}

void allOn() {
  /* turn on all LEDs */
  digitalWrite(LED_BUILTIN, LOW);
  matrix[0].clear();
  matrix[0].fillRect(0,0, 8,16, LED_ON);
  matrix[0].writeDisplay();
  matrix[1].clear();
  matrix[1].fillRect(0,0, 8,16, LED_ON);
  matrix[1].writeDisplay();
  matrixrow.clear();
  matrixrow.fillRect(0,0, 8,16, LED_ON);
  matrixrow.writeDisplay();
  digitalWrite(1,HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
}

void allOff() {
  /* turn off all LEDs */
  digitalWrite(LED_BUILTIN, LOW);
  matrix[0].clear();
  matrix[0].writeDisplay();
  matrix[1].clear();
  matrix[1].writeDisplay();
  matrixrow.clear();
  matrixrow.writeDisplay();
  digitalWrite(1,LOW);
  digitalWrite(LED_BUILTIN, HIGH);
}

void miscOn() {
  /* turn on all LEDs */
  digitalWrite(LED_BUILTIN, LOW);
  eyesOn();
  matrixrow.writeDisplay();
  digitalWrite(1,HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
}


void eyesSet(int n) {
  if (n > 9) n = 9;
  if (n < 0)  n = 0;

  int a = 0;
  if (n == 4 || n == 9) a = 1;
  if (n > 4 && n < 9) a = 3;

  int b=0, c=0;
  if (n < 4) {
    b = n; c = 7-n;
  } else if (n == 4) {
    b = 3; c = 4;
  } else if (n > 4 && n < 9) {
    b = 8-n; c = n-1;
  } else if (n == 9) {
    b = 0; c = 7;
  }
  
  matrixrow.drawPixel(a, b, LED_ON);
  matrixrow.drawPixel(a, c, LED_ON);
}
void eyesOn() {
//  matrixrow.clear();
  matrixrow.fillRect(0,0, 4,16, LED_ON);
}
void eyesOff() {
//  matrixrow.clear();
  matrixrow.fillRect(0,0, 4,16, LED_OFF);
}

void btmRowSet(int n) {
  if (n > 31) n = 31;
  if (n < 0)  n = 0;
  matrixrow.drawPixel(7-(n/8), n%8, LED_ON);
}
void btmRowOn() {
  for (int n=0; n<32; n++)
    matrixrow.drawPixel(7-(n/8), n%8, LED_ON);
}
void btmRowOff() {
  for (int n=0; n<32; n++)
    matrixrow.drawPixel(7-(n/8), n%8, LED_OFF);
}

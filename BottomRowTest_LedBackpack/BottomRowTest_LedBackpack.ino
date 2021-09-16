#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_8x16matrix matrixrow = Adafruit_8x16matrix();

int x = 0, y = 0;

void setup() {
  Serial.begin(115200);
  
  matrixrow.begin(0x70);

  Serial.println("Ready!");
}

void loop() {
  
  Serial.print(y,DEC);
  Serial.print(",");
  Serial.println(x,DEC);

  matrixrow.clear();
  matrixrow.drawPixel(y, x, LED_ON);
  matrixrow.writeDisplay();

  while (Serial.available() < 1) delay(10);
  while (Serial.available() > 0) Serial.read();

  x++;

  if (x > 7) {
    x = 0;
    y++;
    if (y > 15) y = 0;
  }

  
}

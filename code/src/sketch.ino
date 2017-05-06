/* based on https://learn.sparkfun.com/tutorials/graphic-lcd-hookup-guide */
#include <SPI.h>
#include "LCD_Functions.h"

void setup()
{
  Serial.begin(9600);
  digitalWrite(13, 1);

  Serial.println(F("MEMECIMETRO UP"));
  Serial.println(F("lcd begin"));
  lcdBegin(); // This will setup our pins, and initialize the LCD
  Serial.println(F("set contrast"));
  setContrast(40); // Good values range from 40-60

  // Wait for serial to come in, then clear display and go to echo

  clearDisplay(WHITE);
  updateDisplay();

  Serial.println(F("1, 2, 3, 4, 5, 6 cambian de frame"));
}

  updateDisplay();
}

void loop()
{


}

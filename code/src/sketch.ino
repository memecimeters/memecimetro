/* based on https://learn.sparkfun.com/tutorials/graphic-lcd-hookup-guide */

#include "LCD_Functions.h"
//#include "ui_nounny.h"
#include "ui_unny.h"

unsigned int global_clock = 0;
double cadence = 0;

void setup()
{
  Serial.begin(9600);
  digitalWrite(13, 1);

  Serial.println(F("MEMECIMETRO UP"));

  Serial.println(F("lcd begin"));
  lcdBegin(); // This will setup our pins, and initialize the LCD

  Serial.println(F("set contrast"));
  setContrast(40); // Good values range from 40-60

  clearDisplay(WHITE);
  updateDisplay();

}

void loop()
{
  clearDisplay(WHITE);
  //setnounnyHUD();
  setUnnyHUD();
  updateDisplay();

  global_clock++;
  delay(200);
}

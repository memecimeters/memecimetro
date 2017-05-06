/* based on https://learn.sparkfun.com/tutorials/graphic-lcd-hookup-guide */
#include <SPI.h>
#include "LCD_Functions.h"
#include "atlas_gen.h"
unsigned int global_clock = 0;

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

void setCorners() {
  char u = 0, d = LCD_HEIGHT-corner_h, l = 0, r = LCD_WIDTH-corner_w;
  s_corner(0, l, u);
  s_corner(1, r, u);
  s_corner(2, r, d);
  s_corner(3, l, d);
}

void setSpeedBig(double speed) {
  char buf[16], *p, x = 38, y = 3;
  int c;
  dtostrf(speed, 4, 1, buf);
  p = &buf[0];

  while (*p) {
    if ((*p) == '.') { c = 10; x-= font_x2_w/5*2;}
    else { c = *p - '0';}
    s_font_x2(c, x, y);
    x += font_x2_w + 2;
    if ((*p) == '.') { x-= font_x2_w/5*2;}
    p++;
  }
}

void setSpeedCombo() {
  double speed = 12.4;
  setSpeedBig(speed);
  s_speedometer(global_clock % speedometer_len, 8, 3);
}

void setIcons() {
  int x = 18, y = 15, i = 0;
  s_crankset(global_clock % crankset_len, 18, y + (i++)*8);
  s_road(global_clock % road_len, 18, y + (i++)*8);
  s_bars(global_clock % bars_len, 18, y + (i++)*8);
  s_sandclock(global_clock % sandclock_len, 18, y + (i++)*8);
}

void setUnnyHUD() {
  setCorners();
  setSpeedCombo();
  setIcons();


  updateDisplay();
}

void loop()
{
  clearDisplay(WHITE);
  setUnnyHUD();


  global_clock++;
  delay(200);
}

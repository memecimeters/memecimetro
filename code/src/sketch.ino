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

void setBigText(char *s, char x, char y) {
  int c, dx = 0, scale = 2;
  while (*s) {
    if ((*s) == '.') {
       c = 10;
       dx = font_x2_w/5*scale;
    } else if ((*s) == ':') {
       c = 11;
       dx = font_x2_w/5*scale;
    } else {
       c = *s - '0';
       dx = 0;
    }
    x -= dx;
    s_font_x2(c, x, y);
    x += font_x2_w + scale - dx;
    s++;
  }
}

void setText(char *s, char x, char y) {
  int c, dx = 0, scale = 1;
  while (*s) {
    if ((*s) == '.') {
       c = 10;
       dx = font_w/5*scale;
    } else if ((*s) == ':') {
       c = 11;
       dx = font_w/5*scale;
    } else {
       c = *s - '0';
       dx = 0;
    }
    x -= dx;
    s_font(c, x, y);
    x += font_w + scale - dx;
    s++;
  }
}

void setSpeedBig(double speed) {
  char buf[16];
  dtostrf(speed, 4, 1, buf);
  setBigText(buf, 38, 3);
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

void setTime() {
  char x = 28, y = 40;
  char m, s;
  int g = global_clock / 6;
  s = g % 60;
  m = g - s;
  char buf[10];
  snprintf(buf, 10, "%02d:%02d", m, s);
  setText(buf, x, y);
}
void setUnnyHUD() {
  setCorners();
  setSpeedCombo();
  setIcons();
  setTime();


  updateDisplay();
}

void loop()
{
  clearDisplay(WHITE);
  setUnnyHUD();


  global_clock++;
  delay(200);
}

#include "ui_common.h"

#include "atlas_gen.h"

void setCorners() {
  char u = 0, d = HEIGHT-corner_h, l = 0, r = WIDTH-corner_w;
  s_corner(0, l, u);
  s_corner(1, r, u);
  s_corner(2, r, d);
  s_corner(3, l, d);
}

void setBigText(char *s, char x, char y) {
  int c, dx = 0, scale = 3;
  while (*s) {
    if ((*s) == '.') {
       c = 10;
       dx = font_x2_w/5*scale;
    } else if ((*s) == ':') {
       c = 11;
       dx = font_x2_w/5*scale;
    } else if ((*s) == ' ') {
      c = 12;
      dx = 0;
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

void setBiggerText(char *s, char x, char y) {
  int c, dx = 0, scale = 2;
  while (*s) {
    if ((*s) == '.') {
       c = 10;
       dx = font_x3_w/5*scale;
    } else if ((*s) == ':') {
       c = 11;
       dx = font_x3_w/5*scale;
    } else if ((*s) == ' ') {
      c = 12;
      dx = 0;
    } else {
       c = *s - '0';
       dx = 0;
    }
    x -= dx;
    s_font_x3(c, x, y);
    x += font_x3_w + scale - dx;
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
    } else if ((*s) == ' ') {
      c = 12;
      dx = 0;
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

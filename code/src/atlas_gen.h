/// generado por atlas_codegen.py
#ifndef _ATLAS_GEN_H
#define _ATLAS_GEN_H

#include <avr/pgmspace.h>

void blit_cols(const char *p, char h, char r, char c, char x, char y);

#define bars_len 5
#define bars_w 7
#define bars_h 7
extern const char pgm_bars[5][7] PROGMEM;
void s_bars(char frame, char x, char y);

#define corner_len 4
#define corner_w 3
#define corner_h 3
extern const char pgm_corner[4][3] PROGMEM;
void s_corner(char frame, char x, char y);

#define crankset_len 14
#define crankset_w 7
#define crankset_h 7
extern const char pgm_crankset[14][7] PROGMEM;
void s_crankset(char frame, char x, char y);

#define font_len 13
#define font_w 5
#define font_h 5
extern const char pgm_font[13][5] PROGMEM;
void s_font(char frame, char x, char y);

#define font_x2_len 13
#define font_x2_w 10
#define font_x2_h 10
extern const char pgm_font_x2[13][20] PROGMEM;
void s_font_x2(char frame, char x, char y);

#define font_x3_len 13
#define font_x3_w 15
#define font_x3_h 15
extern const char pgm_font_x3[13][30] PROGMEM;
void s_font_x3(char frame, char x, char y);

#define road_len 4
#define road_w 7
#define road_h 7
extern const char pgm_road[4][7] PROGMEM;
void s_road(char frame, char x, char y);

#define sandclock_len 4
#define sandclock_w 7
#define sandclock_h 7
extern const char pgm_sandclock[4][7] PROGMEM;
void s_sandclock(char frame, char x, char y);

#define speedometer_len 7
#define speedometer_w 27
#define speedometer_h 10
extern const char pgm_speedometer[7][54] PROGMEM;
void s_speedometer(char frame, char x, char y);



#endif

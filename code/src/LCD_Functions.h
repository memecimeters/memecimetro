#ifndef _LCD_FUNCTIONS_H
#define _LCD_FUNCTIONS_H
#include <avr/pgmspace.h>

/* PCD8544-specific defines: */
#define LCD_COMMAND  0
#define LCD_DATA     1

/* 84x48 LCD Defines: */
#define LCD_WIDTH   84 // Note: x-coordinates go wide
#define LCD_HEIGHT  48 // Note: y-coordinates go high
#define WHITE       0  // For drawing pixels. A 0 draws white.
#define BLACK       1  // A 1 draws black.

/* Font table:
This table contains the hex values that represent pixels for a
font that is 5 pixels wide and 8 pixels high. Each byte in a row
represents one, 8-pixel, vertical column of a character. 5 bytes
per character. */
extern const unsigned char ASCII[][5] PROGMEM;
/* The displayMap variable stores a buffer representation of the
pixels on our display. There are 504 total bits in this array,
same as how many pixels there are on a 84 x 48 display.

Each byte in this array covers a 8-pixel vertical block on the
display. Each successive byte covers the next 8-pixel column over
until you reach the right-edge of the display and step down 8 rows.

To update the display, we first have to write to this array, then
call the updateDisplay() function, which sends this whole array
to the PCD8544.

Because the PCD8544 won't let us write individual pixels at a
time, this is how we can make targeted changes to the display. */
extern unsigned char displayMap[LCD_WIDTH * LCD_HEIGHT / 8];

void LCDWrite(char data_or_command, char data);
void setPixel(int x, int y, char bw);
void setPixel(int x, int y);
void clearPixel(int x, int y);
void setChar(char character, int x, int y, char bw);
void setStr(char * dString, int x, int y, char bw);

void setBitmap(const char * bitArray);

void clearDisplay(char bw);

void gotoXY(int x, int y);

void updateDisplay();

void setContrast(char contrast);

void invertDisplay();

void lcdBegin(void);

#endif

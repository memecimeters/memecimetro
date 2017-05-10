#include "LCD_Functions.h"
#include "blit_cols.h"

void blit_cols(const unsigned char *p, char h, char r, char c, char x, char y) {
    // TODO: optimizar, cachos de columna en vez de pixel a pixel
    char i, j, t, b;
    for(t=0; t<r; t++) {
        for(i=0; i<c; i++) {
            for(j=0; j<8; j++) {
                b = pgm_read_byte(p+i+t*c);
                if (b & (1 << j)) {
                    setPixel (x+i, y+j+t*8);
                }
            }
        }
    }
};

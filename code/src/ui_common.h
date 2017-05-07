#ifndef _UI_COMMON_H
#define _UI_COMMON_H

#define WIDTH  84
#define HEIGHT 48

extern unsigned int global_clock;
extern double cadence;

void setCorners();
void setBigText(char *s, char x, char y);
void setBiggerText(char *s, char x, char y);
void setText(char *s, char x, char y);

#endif

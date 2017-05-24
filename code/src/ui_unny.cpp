#include "ui_unny.h"

#include <Arduino.h>
#include "sprites_gen.h"
#include "ui_common.h"
#include "LCD_Functions.h"
#include "sleep.h"
#include "clock.h"
#include "config.h"
/*
     /.--------. <<<<*>>>>  .--------.
    / .-----.  \  ,#####,  /  .-----. \
   / /{{{{{{{`. \ #_   _# / .`}}} }}}\ \
  / /{{ {{{ {{ ".\|6` `6|/."}} }}}} }}\ \
 { {{ {{{ {{{{ {{;|  u  |;} }} }} }} }}} }
 { {{{{ {{{{ {{{{ \  =  /}}} }} }} }}} } }
 { { {{{ {{{{{ {{{|\___/|} }} }} }}}} }} }
 { {{{ {{{ {{____/:     :\____}}}}}} }}} }
 { {{{{.'"""`.-===-\   /-===-.`"""'.}} } }
 { {{{/           ""-.-""           \}}} }
   \ \/'       ＡＮＧＥＬＩＴＯ        '\/ /
*/

// DRAW THE SPEED NUMBER
void setUnnySpeedBig(double speed) {
  char buf[16];
  dtostrf(speed, 4, 1, buf);
  if(SPEED_FONT_SIZE == 1){
    setBigText(buf, SPEED_NUMBER_X, SPEED_NUMBER_Y);
  }
  if(SPEED_FONT_SIZE == 2) {
    setBiggerText(buf, SPEED_NUMBER_X, SPEED_NUMBER_Y);
  }
}

// DRAW THE SPEED IMAGE
void setUnnySpeedCombo(double speed) {
  setUnnySpeedBig(speed);
  s_speedometer(global_clock % speedometer_len, SPEED_IMAGE_X, SPEED_IMAGE_Y);
}

// DRAW THE ICON SET
void setUnnyIcons() {
  int x = ICONSET_LEFT_X, y = ICONSET_LEFT_Y, i = 0;
  Serial.println(ICONSET_LEFT_Y);
  Serial.println(ICONSET_LEFT_X);
  s_crankset(global_clock % crankset_len, ICONSET_LEFT_X, y + (i++)*8);
  s_road(global_clock % road_len, x, y + (i++)*8);
  s_bars(global_clock % bars_len, x, y + (i++)*8);
  s_sandclock(global_clock % sandclock_len, x, y + (i++)*8);
}
void setnounnyIconsleft() {
  int x = ICONSET_LEFT_X, y = ICONSET_LEFT_Y, i = 0;
  s_crankset(global_clock/4 % crankset_len, x, y + (i++)*8);
  s_road(global_clock/4 % road_len, x, y + 4 + (i++)*8);
}
void setnounnyIconsright() {
  int x = ICONSET_RIGHT_X, y = ICONSET_RIGHT_Y, i = 0;
  s_bars(global_clock/4 % bars_len, x, y + (i++)*4);
  s_sandclock(global_clock/4 % sandclock_len, x, y + 4 + (i++)*8);
}


// DRAW THE CADENCE NUMBER
void setUnnyCadence(double cadence) {
  char buf[16];
  dtostrf(cadence, 4, 1, buf);
  setText(buf, CADENCE_NUMBER_X, CADENCE_NUMBER_Y);
}

// DRAW THE AVG NUMBER
void setUnnyAVG(double avg) {
  char buf[16];
  dtostrf(avg, 4, 1, buf);
  setText(buf, AVG_NUMBER_X, AVG_NUMBER_Y);
}

// DRAW THE TIME NUMBER
void setUnnyTime() {
  char buf[10];
  snprintf(buf, 10, "%02d:%02d", currentMinutes(), currentSeconds());
  setText(buf, TIME_NUMBER_X, TIME_NUMBER_Y);
}

// DRAW THE DISTANCE NUMBER
void setUnnyDistance(double dist) {
  char buf[16];
  dtostrf(dist, 5, 1, buf);
  setText(buf, DISTANCE_NUMBER_X, DISTANCE_NUMBER_Y);
}

// RENDER THE HEAD-UP DISPLAYe
void setUnnyHUD(double speed, double cadence, double avg, double dist) {
  if(CORNER_ICONS_SET == 1) {
  setCorners();
  }
  setUnnySpeedCombo(speed); // X
  if(ICONSET_ROWS == 1) {
    setUnnyIcons(); //X
  } else {
    setnounnyIconsleft();
    setnounnyIconsright();
  }
  setUnnyCadence(cadence); //X
  setUnnyAVG(avg);
  setUnnyTime();
  setUnnyDistance(dist); //X
}

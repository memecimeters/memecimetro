#include "ui_nounny.h"

#include <Arduino.h>

#include "sprites.h"
#include "ui_common.h"


void setnounnySpeedBig(double speed) {
  char buf[16];
  dtostrf(speed, 4, 1, buf);
  setBiggerText(buf, 29, 6);
}

void setnounnySpeedCombo() {
  double speed = 44;
  setnounnySpeedBig(speed);
  s_speedometer(global_clock/4 % speedometer_len, 1, 6);
}

void setnounnyIconsleft() {
  int x = 3, y = 27, i = 0;
  s_crankset(global_clock/4 % crankset_len, 3, y + (i++)*8);
  s_road(global_clock/4 % road_len, 3, y + 4 + (i++)*8);
}

void setnounnyIconsright() {
  int x = 47, y = 27, i = 0;
  s_bars(global_clock/4 % bars_len, 47, y + (i++)*4);
  s_sandclock(global_clock/4 % sandclock_len, 47, y + 4 + (i++)*8);
}

void setnounnyCadence() {
  if (global_clock % 6 == 0) {
    cadence = random(100);
  }
  char buf[10];
  snprintf(buf, 10, "%4d", cadence);
  setText(buf, 10, 28);
}

void setnounnyDistance() {
  char buf[16];
  double dist = 1.2f*global_clock;
  if (dist > 9999.9) {
    dist = 9999.9;
  }
  dtostrf(dist, 5, 1, buf);
  setText(buf, 10, 31 + crankset_h + 2);
}

void setnounnyTime() {
  char x = 48 + bars_w, y = 31 + bars_h + 2;
  char m, s;
  int g = global_clock / 6;
  s = g % 60;
  m = g - s;
  char buf[10];
  snprintf(buf, 10, "%02d:%02d", m, s);
  setText(buf, x, y);
}

void setnounnyHUD() {
  //setCorners();
  setnounnySpeedCombo();
  setnounnyIconsleft();
  setnounnyIconsright();

  setnounnyCadence();
  setnounnyDistance();
  // MAX SPEED VA ACÁ
  setnounnyTime();
}

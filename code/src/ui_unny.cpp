#include "ui_unny.h"

#include <Arduino.h>

#include "atlas_gen.h"
#include "ui_common.h"


void setUnnySpeedBig(double speed) {
  char buf[16];
  dtostrf(speed, 4, 1, buf);
  setBigText(buf, 38, 3);
}

void setUnnySpeedCombo() {
  double speed = 12.4;
  setUnnySpeedBig(speed);
  s_speedometer(global_clock % speedometer_len, 8, 3);
}

void setUnnyIcons() {
  int x = 18, y = 15, i = 0;
  s_crankset(global_clock % crankset_len, 18, y + (i++)*8);
  s_road(global_clock % road_len, 18, y + (i++)*8);
  s_bars(global_clock % bars_len, 18, y + (i++)*8);
  s_sandclock(global_clock % sandclock_len, 18, y + (i++)*8);
}

void setUnnyCadence() {
  if (global_clock % 6 == 0) {
    cadence = random(100);
  }
  char buf[10];
  snprintf(buf, 10, "%4d", cadence);
  setText(buf, 22, 16);
}

void setUnnyTime() {
  char x = 28, y = 40;
  char m, s;
  int g = global_clock / 6;
  s = g % 60;
  m = g - s;
  char buf[10];
  snprintf(buf, 10, "%02d:%02d", m, s);
  setText(buf, x, y);
}

void setUnnyDistance() {
  char buf[16];
  double dist = 1.2f*global_clock*global_clock;
  if (dist > 9999.9) {
    dist = 9999.9;
  }
  dtostrf(dist, 5, 1, buf);
  setText(buf, 28, 24);
}

void setUnnyHUD() {
  setCorners();
  setUnnySpeedCombo();
  setUnnyIcons();

  setUnnyCadence();
  setUnnyDistance();
  // MAX SPEED VA ACÁ
  setUnnyTime();
}

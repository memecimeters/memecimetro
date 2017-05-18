#include "clock.h"
#include <avr/sleep.h>
#include "Arduino.h"
#include "LCD_Functions.h"
#include "sleep.h"
#include "le_wild_vars.h"
int lastActionTime;

void wakeUpNow() {
  Serial.println("-[=[   ＷＡＫＩＮＧ　ＵＰ   ]=]-");
  analogWrite(BACKLIGHT_PIN, 255);
  registerActionTime();
}

void sleepNow() {
  clearDisplay(0);
  analogWrite(BACKLIGHT_PIN, 0);
  updateDisplay();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  attachInterrupt(0,wakeUpNow, LOW);
  sleep_mode();
  sleep_disable();
  // THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP
  detachInterrupt(0);
}

void checkSleepTime() {
  if(currentTime() >= (lastActionTime + SLEEP_THRESHOLD_SECS)) {
    Serial.println("-[=[   ＳＬＥＥＰ　ＴＩＭＥ   ]=]-");
    sleepNow();
  }
}

void registerActionTime() {
  Serial.println("-[=[   ＡＣＴＩＯＮ　ＲＥＧＩＳＴＥＲＥＤ   ]=]-");
  lastActionTime = currentTime();
}

#include "clock.h"
#include <avr/sleep.h>
#include "Arduino.h"
#include "LCD_Functions.h"
#include "sleep.h"
#include "config.h"
int lastActionTime;

void wakeUpNow() {
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

bool shouldISleepNow() {
  return currentTime() >= (lastActionTime + SLEEP_THRESHOLD_SECS); 
}

void registerActionTime() {
  lastActionTime = currentTime();
}

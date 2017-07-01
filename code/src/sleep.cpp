#include "clock.h"
#include <avr/sleep.h>
#include "Arduino.h"
#include "LCD_Functions.h"
#include "sleep.h"
#include "config.h"

int lastActionTime;

void wakeUpNow() {
  detachInterrupt(digitalPinToInterrupt(2));
  turnOnBacklight();
  registerActionTime();
}

void sleepNow() {
  clearDisplay(0);
  turnOffBacklight();
  updateDisplay();
  attachInterrupt(digitalPinToInterrupt(2), wakeUpNow, LOW);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
  sleep_disable();
}

bool shouldISleepNow() {
  return currentTime() >= (lastActionTime + SLEEP_THRESHOLD_SECS);
}

void registerActionTime() {
  lastActionTime = currentTime();
}

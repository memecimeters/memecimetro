#include "Arduino.h"

int currentTime() {
  return millis()/1000;
}

int currentSeconds() {
  return (millis()/1000) % 60;
}

int currentMinutes() {
  return ((millis()/1000) / 60) % 60;
}

int currentHours() {
  return (((millis()/1000) / 60) / 60) % 60;
}

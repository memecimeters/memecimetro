/* based on https://learn.sparkfun.com/tutorials/graphic-lcd-hookup-guide */

#include "Arduino.h"
#include "HardwareSerial.h"
#include "ui_unny.h"
#include "LCD_Functions.h"
#include "sleep.h"
#include "clock.h"
#include "config.h"
#include "EEPROM.h"
#include "EEPROMAnything.h"
#include "SoftReset.h"

#define reed A0
unsigned int global_clock = 0;
int reedVal;
long timer;
double kmh;
double rpm;
double average;
double distance;
double memoryDistance;
double displayDistance;
float radius = WHEEL_RADIUS_CSM;
float circumference;
int maxReedCounter = 100;//min time (in ms) of one rotation (for debouncing)
int reedCounter;
int reedCounterTotal;
int wakePin = 2;
bool sendToSleep = false;
float pressLength_milliSeconds = 0;

void setup()
{
  Serial.begin(115200);
  digitalWrite(13, 1);

  EEPROM_readAnything(0, memoryDistance);
  if (memoryDistance != memoryDistance) {
    memoryDistance = 0;
  }
  displayDistance = memoryDistance;

  reedCounter = maxReedCounter;
  circumference = 2*3.14159*radius;
  pinMode(reed, INPUT_PULLUP);
  pinMode(wakePin, INPUT_PULLUP);
  turnOffBacklight();

  // TIMER SETUP- the timer interrupt allows precise timed measurements of the reed switch
  //for more info about configuration of arduino timers see http://arduino.cc/playground/Code/Timer1
  cli();//stop interrupts

  //set timer1 interrupt at 1kHz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;
  // set timer count for 1khz increments
  OCR1A = 1999;// = (1/1000) / ((1/(16*10^6))*8) - 1
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS11 bit for 8 prescaler
  TCCR1B |= (1 << CS11);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei();//allow interruptsdo

  lcdBegin(); // This will setup our pins, and initialize the LCD
  updateDisplay();
  setContrast(40); // Good values range from 40-60

  delay(300); // give some time for serial connection

  clearDisplay(WHITE);
  updateDisplay();

}

ISR(TIMER1_COMPA_vect) {//Interrupt at freq of 1kHz to measure reed switch
  reedVal = digitalRead(reed);//get val of A0
  if (!reedVal){//if reed switch is closed
    if (reedCounter == 0){//min time between pulses has passed
      kmh = (91.4*float(circumference))/float(timer);//calculate km/h = 1/(inches per km) * (miliseconds per hr) * (circumference / timer) = 91.4
      rpm = (kmh / WHEEL_DEVELOPMENT)/60; //http://www.tariksaleh.com/bike/geartospeed.pdf
      reedCounterTotal = 1 + reedCounterTotal;
      distance = reedCounterTotal * circumference * 2.54e-5;
      displayDistance = distance + memoryDistance;
      average = distance / ((currentTime() / (double)60) / 60);
      registerActionTime();
      timer = 0;//reset timer
      reedCounter = maxReedCounter;//reset reedCounter
    }
  }
  else{//if reed switch is open
    if (reedCounter > 0){//don't let reedCounter go negative
      reedCounter -= 1;//decrement reedCounter
    }
  }
  if (timer > 2000){
    kmh = 0;//if no new pulses from reed switch- tire is still, set kmh to 0
    rpm = 0;
  }
  else{
    timer += 1;//increment timer
  }
}


void loop()
{

  clearDisplay(WHITE);
  setUnnyHUD(kmh, rpm, average, displayDistance);
  updateDisplay();

  while (digitalRead(wakePin) == LOW ){
    delay(100);
    pressLength_milliSeconds = pressLength_milliSeconds + 100;
  }

  if(shouldISleepNow()){
    EEPROM_writeAnything(0, displayDistance);
    sleepNow();
  }

  if(pressLength_milliSeconds > PRESS_TIME_TO_SLEEP){
    EEPROM_writeAnything(0, displayDistance);
    sleepNow();
    softReset();
  }

  if(pressLength_milliSeconds >= PRESS_TIME_TO_TOGGLE_BACKLIGHT){
    toggleBacklight();
  }

  pressLength_milliSeconds = 0;

  global_clock++;
  delay(200);
}

/* based on https://learn.sparkfun.com/tutorials/graphic-lcd-hookup-guide */

#include "Arduino.h"
#include "HardwareSerial.h"

#include "LCD_Functions.h"
//#include "ui_nounny.h"
#include "ui_unny.h"

#define reed A0
unsigned int global_clock = 0;
double cadence = 0;
int reedVal;
long timer;
double kmh;
float radius = 13.5;
float circumference;
int maxReedCounter = 100;//min time (in ms) of one rotation (for debouncing)
int reedCounter;


void setup()
{
  Serial.begin(9600);
  digitalWrite(13, 1);

  reedCounter = maxReedCounter;
  circumference = 2*3.14*radius;
  pinMode(reed, INPUT_PULLUP);

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

  sei();//allow interrupts

  lcdBegin(); // This will setup our pins, and initialize the LCD
  updateDisplay();
  setContrast(40); // Good values range from 40-60

  delay(300); // give some time for serial connection

  clearDisplay(WHITE);
  updateDisplay();

  Serial.println(F("MEMECIMETRO UP"));

}

ISR(TIMER1_COMPA_vect) {//Interrupt at freq of 1kHz to measure reed switch
  reedVal = digitalRead(reed);//get val of A0
  if (!reedVal){//if reed switch is closed
    if (reedCounter == 0){//min time between pulses has passed
      kmh = (91.4*float(circumference))/float(timer);//calculate km/h = 1/(inches per km) * (miliseconds per hr) * (circumference / timer) = 91.4
      timer = 0;//reset timer
      reedCounter = maxReedCounter;//reset reedCounter
    }
    else{
      if (reedCounter > 0){//don't let reedCounter go negative
        //reedCounter -= 1;//decrement reedCounter
      }
    }
  }
  else{//if reed switch is open
    if (reedCounter > 0){//don't let reedCounter go negative
      reedCounter -= 1;//decrement reedCounter
    }
  }
  if (timer > 2000){
    kmh = 0;//if no new pulses from reed switch- tire is still, set kmh to 0
  }
  else{
    timer += 1;//increment timer
  }
}

void loop()
{
  clearDisplay(WHITE);
  //setnounnyHUD();
  setUnnyHUD(kmh);
  updateDisplay();

  global_clock++;
  delay(200);
}

#include "kernel.h"
#include "config.h"
#include "core.h"
#include "input.h" 
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4);

void setup() {
  Serial.begin(9600);  
  initInput();
  changeState(INTRO_STATE);
}

void loop(){ 
  updateStateTime(); 
  switch (getCurrentState()) { 
  case INTRO_STATE:
    intro(lcd);
    break;
  case DEALER_STATE:
    break;
  case GUESS_STATE:
    break;
  case FINAL_STATE:
    break;
  }
}


#include "kernel.h"
#include "config.h"
#include "core.h"
#include "input.h" 



void setup() {
  Serial.begin(9600);  
  initInput();
  changeState(INTRO_STATE);
}

void loop(){ 
  updateStateTime(); 
  switch (getCurrentState()) { 
  case INTRO_STATE:
    intro();
    break;
  case DEALER_STATE:
    generateSequence();
    break;
  case GUESS_STATE:
    break;
  case FINAL_STATE:
    break;
  }
}


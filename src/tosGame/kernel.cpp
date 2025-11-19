#include "kernel.h"

int currentState;

unsigned long enteredStateTime;

unsigned long currentTimeInState;

bool firstCheckInState; 


int getCurrentState(){
  return currentState;
}

long getCurrentTimeInState(){
  return currentTimeInState;
}

long getEnteredStateTime(){
  return enteredStateTime;
}

bool isJustEnteredInState(){
  bool com = firstCheckInState;
  firstCheckInState = false;
  return com;
}

void changeState(int new_state){
  currentState = new_state;
  enteredStateTime = millis();
  firstCheckInState = true;
}

void updateStateTime(){
  currentTimeInState = millis() - enteredStateTime;
}

void logMsg(const String& msg){
  #ifdef __DEBUG__
  Serial.println(msg);
  #endif
}


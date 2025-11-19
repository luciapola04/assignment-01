#include "input.h"
#include "Arduino.h"

#include <EnableInterrupt.h>

#define BOUNCING_TIME 200

uint8_t inputPins[NUM_BTNS] = {BTN_1, BTN_2,BTN_3,BTN_4};
bool buttonPressed[NUM_BTNS] = {false, false, false, false};

unsigned long lastButtonPressedTimestamps[NUM_BTNS];

void buttonHandler(int i);
void buttonHandler1(){ buttonHandler(0); }
void buttonHandler2(){ buttonHandler(1); }
void buttonHandler3(){ buttonHandler(2); }
void buttonHandler4(){ buttonHandler(3); }

void (*buttonHandlers[NUM_BTNS])() = { buttonHandler1, buttonHandler2,buttonHandler3,buttonHandler4  };

void buttonHandler(int i){
  long ts = millis();
  if (ts - lastButtonPressedTimestamps[i] > BOUNCING_TIME){
    lastButtonPressedTimestamps[i] = ts;
    int status = digitalRead(inputPins[i]);
    if (status == HIGH && !buttonPressed[i]) { 
        buttonPressed[i] = true;
    }
  }
}

void initInput(){
  for (int i = 0; i < NUM_BTNS; i++) {
    pinMode(inputPins[i], INPUT);
    enableInterrupt(inputPins[i], buttonHandlers[i], CHANGE);   
  }
}

void resetInput(){
  long ts = millis();
  for (int i = 0; i < NUM_BTNS; i++) {
    buttonPressed[i] = false;      
    lastButtonPressedTimestamps[i] = ts;    
  }
}
bool isButtonPressed(int buttonIndex){
  return buttonPressed[buttonIndex];
}

bool hasBeenPressed(int index){
  return buttonPressed[index]; 
}





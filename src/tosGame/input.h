#ifndef __INPUT__
#define __INPUT__

#include "config.h"

extern bool buttonPressed[NUM_BTNS];

void initInput();
void resetInput();
bool isButtonPressed(int buttonIndex);
 
#endif

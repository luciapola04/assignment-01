#ifndef __INPUT__
#define __INPUT__


extern bool buttonPressed[4] = {false, false,false,false};

void initInput();
void resetInput();
bool isButtonPressed(int buttonIndex);
 
#endif

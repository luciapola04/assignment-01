#ifndef __CORE__
#define __CORE__

#define INTRO_STATE   1
#define DEALER_STATE  2
#define GUESS_STATE  3
#define FINAL_STATE   4 

#include <LiquidCrystal_I2C.h>

void intro();
void sleeping();
void generateSequence();
void checkSequence();
void gameOver();

#endif

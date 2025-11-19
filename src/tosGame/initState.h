#ifndef INIT_STATE
#define INIT_STATE

#include <LiquidCrystal_I2C.h>

void initScreen(LiquidCrystal_I2C &lcd);
void fading();
void deepSleep(LiquidCrystal_I2C &lcd);
void wakeUp();

extern bool initState;            
extern unsigned long initStartTime;
extern unsigned long initInterval; 

void enableInterrupt(uint8_t pin, void (*userFunction)(), uint8_t mode);
void disableInterrupt(uint8_t pin);

#endif

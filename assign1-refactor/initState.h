// initState_fixed.h
#ifndef INIT_STATE
#define INIT_STATE

#include <LiquidCrystal_I2C.h>

void initScreen(LiquidCrystal_I2C &lcd);
void faiding();
void deepSleep(LiquidCrystal_I2C &lcd);
void wakeUp();

extern bool initState;            // stato "intro" attivo
extern unsigned long initStartTime;
extern unsigned long initInterval; // timeout intro
// Dichiarazioni per l'uso in initState.cpp
void enableInterrupt(uint8_t pin, void (*userFunction)(), uint8_t mode);
void disableInterrupt(uint8_t pin);


#endif

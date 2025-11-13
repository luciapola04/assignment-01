#ifndef INITSCREENLIB_H
#define INITSCREENLIB_H

#include <LiquidCrystal_I2C.h>
#include "config.h"

extern bool initState;

void initScreen(LiquidCrystal_I2C &lcd);
void updateInitState(LiquidCrystal_I2C &lcd);
void faiding();
void deepSleep(LiquidCrystal_I2C &lcd);

#endif
#include "initState.h"
#include <Arduino.h>
#include <avr/sleep.h>

int intensity = 0;
int fadeAmount = 5;
unsigned long lastFadeTime = 0;
unsigned long fadeInterval = 20; 
bool initState = false;
unsigned long initStartTime = 0;
int initInterval = 10000;

void faiding() {
    int currentMillis = millis();
    if (currentMillis - lastFadeTime >= fadeInterval) {
        lastFadeTime = currentMillis;
        analogWrite(RED_PIN, intensity);
        intensity += fadeAmount;
        if (intensity <= 0 || intensity >= 255) {
          fadeAmount = -fadeAmount;
        }
      }
}

void initScreen(LiquidCrystal_I2C &lcd) {
    
    initStartTime = millis();
    initState = true;
    lcd.init(); 
    lcd.backlight(); 
    lcd.setCursor(2, 0); 
    lcd.print("Welcome to TOS!"); 
    lcd.setCursor(5, 1); 
    lcd.print("Press B1"); 
    lcd.setCursor(5, 2); 
    lcd.print("to Start");
}

void wakeUp() {}

void deepSleep(LiquidCrystal_I2C &lcd) {
    lcd.clear();
    lcd.setCursor(5, 1);
    lcd.print("SLEEPING...");
    lcd.setCursor(0, 2);
    lcd.print("Press B1 to wake up!");
    digitalWrite(RED_PIN, LOW);
    attachInterrupt(digitalPinToInterrupt(btns_pin[0]), wakeUp, RISING);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
  
    sleep_disable();
    detachInterrupt(digitalPinToInterrupt(btns_pin[0]));
    initScreen(lcd);
}

void updateInitState(LiquidCrystal_I2C &lcd) {
    if (initState) {
        faiding();
        if (digitalRead(btns_pin[0]) == HIGH) { 
            initState = false;
        }
        if (millis() - initStartTime >= initInterval) { 
            initState = false;
            deepSleep(lcd);
        }
    }
}

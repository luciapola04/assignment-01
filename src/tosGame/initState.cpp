#include "initState.h"
#include <Arduino.h>
#include <avr/sleep.h>
#include "config.h"
#include "input.h"

int intensity = 0;
int fadeAmount = 5;

unsigned long lastFadeTime = 0;
unsigned long fadeInterval = 20UL;
unsigned long initStartTime = 0;
unsigned long initInterval = 10000UL;

bool initState = false;

void fading() {
  unsigned long currentMillis = millis();
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

void wakeUp() {
  (void)0;
}

void deepSleep(LiquidCrystal_I2C &lcd) {
  lcd.clear();
  lcd.setCursor(5, 1);
  lcd.print("SLEEPING...");
  lcd.setCursor(0, 2);
  lcd.print("Press B1 to wake up!");
  digitalWrite(RED_PIN, LOW);
  enableInterrupt(BTN_1, wakeUp, RISING);

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode(); 

  sleep_disable();
  disableInterrupt(BTN_1);
  initInput();
  initScreen(lcd);
}


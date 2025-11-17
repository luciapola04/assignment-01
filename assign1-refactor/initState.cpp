// initState_fixed.cpp
#include "initState.h"
#include <Arduino.h>
#include <avr/sleep.h>

#include <EnableInterrupt.h>
#include "config.h" // per RED_PIN, btns_pin[], ecc.

int intensity = 0;
int fadeAmount = 5;

// tempi -> unsigned long PERFORTEZZA
unsigned long lastFadeTime = 0;
unsigned long fadeInterval = 20UL;

bool initState = false;
unsigned long initStartTime = 0;
unsigned long initInterval = 10000UL; // ora unsigned long

// fade: usare unsigned long per millis
void faiding() {
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
  // ISR vuota: serve solo a risvegliare la MCU
  // Tenere il più breve possibile
  (void)0;
}

void deepSleep(LiquidCrystal_I2C &lcd) {
  lcd.clear();
  lcd.setCursor(5, 1);
  lcd.print("SLEEPING...");
  lcd.setCursor(0, 2);
  lcd.print("Press B1 to wake up!");
  digitalWrite(RED_PIN, LOW);

  // --- abilita interrupt sul pin BTN_1 ---
  // RISING se il pulsante normalmente sta LOW -> HIGH quando premuto
  // FALLING se usi INPUT_PULLUP e il pulsante va a GND
  enableInterrupt(BTN_1, wakeUp, RISING);

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();  // La MCU DORME qui. Si sveglia solo sull'interrupt.

  // --- codice eseguito DOPO il risveglio ---
  sleep_disable();
  disableInterrupt(BTN_1);

  initScreen(lcd);
}


#include "faidingLed.h"
#include "config.h"
#include <Arduino.h>

int intensity = 0;
int fadeAmount = 5;
unsigned long lastFadeTime = 0;
unsigned long fadeInterval = 20;

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
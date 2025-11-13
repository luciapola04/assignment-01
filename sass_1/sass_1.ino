#include <LiquidCrystal_I2C.h>
#include "config.h"
#include "initState.h"

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4);
int lastSequenceTime = 0;   
int  sequenceInterval = 3000;
bool gameStarted = false;

void setup() { 
  pinMode(RED_PIN, OUTPUT);
  for (int i = 0; i<NUM_BTNS; i++) {
  	pinMode(btns_pin[i], INPUT);
  }
  initScreen(lcd);
  randomSeed(analogRead(A4)); 
  Serial.begin(9600);
}

void loop() {
  if (!gameStarted) {
    updateInitState(lcd);
    if(!initState) {
      gameStarted = true;
      digitalWrite(RED_PIN, LOW);
    }
  } else {
    StartGame();
  }
}

void StartGame() {
  int currentMillis = millis();
  if (currentMillis - lastSequenceTime >= sequenceInterval) {
    lastSequenceTime = currentMillis; 
    lcd.clear();
    lcd.setCursor(5, 1);
    lcd.print("Sequenza:");
    lcd.setCursor(7, 2);
    int nums[] = {1, 2, 3, 4};
        for (int i = 3; i > 0; i--) {
            int j = random(0, i + 1);
            int temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;
        }
        for (int i = 0; i < 4; i++) {
            lcd.print(nums[i]);
        }
  }
}


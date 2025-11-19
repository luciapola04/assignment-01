#include "core.h"
#include "Arduino.h"
#include "kernel.h"
#include "input.h"
#include "config.h"
#include "initState.h"

#define INTRO_INT 10000
#define RED_INT

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4);

int nums[NUM_BTNS] = {1, 2, 3, 4};
int currentNumber = 0;
int score = 0;
int current;

unsigned long t1 = T1;
unsigned long f = F;

long gameOverStartTime = 0;
bool gameOverInit = false;


void intro() {
  if (isJustEnteredInState()) {
    Serial.println("Intro...");
    initScreen(lcd);
  }
  faiding();

  if (digitalRead(BTN_1) == HIGH) {
    int pot = analogRead(POT_PIN);  
    int L = map(pot, 0, 1023, 1, 5); 

    if (L < 1) L = 1;
    if (L > 4) L = 4;
    lcd.clear();
    lcd.setCursor(2, 1);
    lcd.print("Difficulty: ");
    lcd.print(L);
    delay(3000);

    switch (L) {
      case 1:
        f = F - 1500;
        break;
      case 2:
        f = F - 1000;
        break;
      case 3:
        f = F - 500;
        break;
      case 4:
        f = F;
        break;
    }
    digitalWrite(RED_PIN, LOW);
    lcd.clear();
    lcd.setCursor(5, 1);
    lcd.print("GO!");
    delay(2000);
    changeState(DEALER_STATE); 
    return;
  }

  unsigned long dt = getCurrentTimeInState();
  if (dt > INTRO_INTERVAL) {
    deepSleep(lcd);
    changeState(INTRO_STATE);
    return;
  }
}

void generateSequence(){
  
  if (isJustEnteredInState()){
    Serial.println("Generate Sequence...");
    resetInput();
  }

  lcd.clear();
  lcd.setCursor(5, 1);
  lcd.print("Sequenza:");
  lcd.setCursor(5, 2);
  for (int i = 3; i > 0; i--) {
    int j = random(0, i + 1);
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
  }
  for (int i = 0; i < 4; i++) {
    lcd.print(nums[i]);
    Serial.print(nums[i]);
  }

  changeState(GUESS_STATE);
}

void checkSequence(){
  if (isJustEnteredInState()){
    Serial.println("checkSequence...");
  }

  for(int i = 0; i < NUM_BTNS; i++){

    if (isButtonPressed(i)) {
      resetInput();
      Serial.print(i);
      if (nums[currentNumber] == (i + 1)) {
        currentNumber++;
      } else {
        t1=T1;
        resetInput();
        changeState(FINAL_STATE);
      }
    }
  }

  if(currentNumber>=NUM_BTNS){ 
    score ++;
    lcd.clear();
    lcd.setCursor(5, 1);
    lcd.print("GOOD! Score: ");
    lcd.print(score);
    currentNumber = 0;
    t1=t1-f;
    delay(2000);
    changeState(DEALER_STATE);

  }
  
  if(getCurrentTimeInState() > t1){
    changeState(FINAL_STATE);          
  }
}



void gameOver(){
  if (isJustEnteredInState()){
    Serial.println("Finalize...");
  }
  long currentMillis = millis();
  if (!gameOverInit) {
    digitalWrite(RED_PIN, HIGH);
    gameOverStartTime = currentMillis;
    lcd.clear();
    lcd.setCursor(5, 1);
    lcd.print("Game Over");
    lcd.setCursor(3, 2);
    lcd.print("Final Score: ");
    lcd.print(score);
    gameOverInit = true;
  }

  if (currentMillis - gameOverStartTime >= RED_INT) {
    digitalWrite(RED_PIN, LOW);
  }

  if (currentMillis - gameOverStartTime >= INTRO_INT) {
    initState = true;
    gameOverInit = false;
    score = 0;
    currentNumber = 0;
    changeState(INTRO_STATE);
  }
}

#include "core.h"
#include "Arduino.h"
#include "kernel.h"
#include "input.h"
#include "config.h"
#include "initState.h"

#define MAX_TIME_IN_INTRO_STATE 10000
//#define MAX_TIME_IN_STAGE2_STATE 10000
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4);

int nums[NUM_BTNS] = {1, 2, 3, 4};
int currentNumber = 0;
int score = 0;

unsigned long t1 = T1;
unsigned long f = F;

long gameOverStartTime = 0;
bool gameOverInit = false;

/* core business logic */

void intro() {
  if (isJustEnteredInState()) {
    Serial.println("Intro...");
    // mostra la schermata di intro (inizializza initStartTime)
    initScreen(lcd);
  }

  // animazione LED
  faiding();

  // se premi B1 -> esci dall'intro (sostituisci NEXT_STATE_ON_BUTTON con il tuo stato di gioco)
  if (digitalRead(BTN_1) == HIGH) {
    // Esempio: changeState(GAME_STATE);
    // Sostituisci con la transizione corretta nella tua applicazione:
    changeState(DEALER_STATE); // <<--- sostituisci questo
    return;
  }

  // timeout dello stato intro: se superato, andiamo in deepSleep e poi in SLEEP_STATE
  unsigned long dt = getCurrentTimeInState();
  if (dt > MAX_TIME_IN_INTRO_STATE) {
    // entri in deep sleep (la funzione non ritorna fino al wake)
    deepSleep(lcd);

    // dopo il wake, puoi cambiare stato a SLEEP_STATE
    changeState(INTRO_STATE);
    return;
  }
}

void generateSequence(){
  
  if (isJustEnteredInState()){
    Serial.println("Generate Sequence...");
    resetInput();
    digitalWrite(RED_PIN, LOW);
    lcd.clear();
    lcd.setCursor(5, 1);
    lcd.print("GO!!");
    delay(2000);
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
  /* change the state if button 0 is pressed */
  /*if (isButtonPressed(0)){
    //changeState(STAGE2_STATE);          
  }*/
}

void checkSequence(){
  if (isJustEnteredInState()){
    Serial.println("checkSequence...");
  }

  for(int i = 0; i < NUM_BTNS; i++){

    if (isButtonPressed(i)) {

            // Consuma la pressione (reset del flag)
            resetInput();
            Serial.print(i);

            // Logica della sequenza
            if (nums[currentNumber] == (i + 1)) {
                currentNumber++;
            } 
            else {
                t1=T1;
                resetInput();
                changeState(FINAL_STATE);
            }
        }
  }

  if(currentNumber>=NUM_BTNS){
    lcd.clear();
    lcd.setCursor(5, 1);
    lcd.print("Hai vinto");
    score ++;
    currentNumber = 0;
    t1=t1-F;
    delay(500);
    changeState(DEALER_STATE);

  }
  
  if(getCurrentTimeInState() > T1){
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
      lcd.print("Hai perso");
      lcd.setCursor(5, 2);
      lcd.print("Score :");
      lcd.print(score);
      gameOverInit = true;
    }

    if (currentMillis - gameOverStartTime >= 2000) {
      digitalWrite(RED_PIN, LOW);
    }

    if (currentMillis - gameOverStartTime >= 10000) {
      
      initState = true;
      gameOverInit = false;
      score = 0;
      currentNumber = 0;
      changeState(INTRO_STATE);
    }

}

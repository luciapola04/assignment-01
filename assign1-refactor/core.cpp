#include "core.h"
#include "Arduino.h"
#include "kernel.h"
#include "input.h"
#include "config.h"
#include "initState.h"

#define MAX_TIME_IN_INTRO_STATE 10000
//#define MAX_TIME_IN_STAGE2_STATE 10000

/* core business logic */

void intro(LiquidCrystal_I2C &lcd) {
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

void stage1(){
  if (isJustEnteredInState()){
    Serial.println("Stage1...");
    resetInput();
  }

  /* change the state if button 0 is pressed */
  if (isButtonPressed(0)){
    //changeState(STAGE2_STATE);          
  }
}

void stage2(){
  if (isJustEnteredInState()){
    Serial.println("Stage2...");
  }

  /* change the state if button 1 is pressed or max time elapsed*/
  /*if (isButtonPressed(1) || getCurrentTimeInState() > MAX_TIME_IN_STAGE2_STATE){
    changeState(FINAL_STATE);          
  }*/
}

void finalize(){
  if (isJustEnteredInState()){
    Serial.println("Finalize...");
  }
  changeState(INTRO_STATE);
}

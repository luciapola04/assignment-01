#include <LiquidCrystal_I2C.h>
#include "config.h"
#include "initState.h"

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4);

int lastSequenceTime = 0;   
int sequenceInterval = 5000;
int score = 0;
int currentNumber = 0;

int nums[NUM_BTNS] = {1, 2, 3, 4};

int lastButtonState[NUM_BTNS] = {0,0,0,0};
int actualButtonState[NUM_BTNS] = {0,0,0,0};
int buttonDelay = 50;
int buttonTimer[NUM_BTNS] = {0,0,0,0};

bool gameOver = false;
bool gameStarted = false;
bool userTurn = false;


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
      lcd.clear();
      lcd.setCursor(5, 1);
      lcd.print("GO!!");
    }
  } else {
    
    if (userTurn){
      checkCorrectSequence();

    }else{
      generateSequence();
      delay(100);
      userTurn = true;
    }
    
  }

  if(gameOver){
    digitalWrite(RED_PIN,HIGH);
    lcd.clear();
    lcd.setCursor(5, 1);
    lcd.print("Hai perso");
    lcd.setCursor(5, 2);
    lcd.print("Score :");
    lcd.print(score);
    delay(10000);

    userTurn=false;
    gameStarted = false;
    gameOver = false;
    
    score = 0;
    currentNumber = 0;

    initScreen(lcd);
  }
}

void generateSequence() {

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
  }
  
}

void checkCorrectSequence(){

  for(int i = 0; i < NUM_BTNS; i++){

    int buttonPressed = digitalRead(btns_pin[i]);

    if(buttonPressed != lastButtonState[i]){
      buttonTimer[i] = millis();
    }

    if(millis()-buttonTimer[i] > buttonDelay){

      if(buttonPressed != actualButtonState[i]){
        actualButtonState[i] = buttonPressed;

        if(actualButtonState[i] == HIGH){
        if(nums[currentNumber] == (i+1)){
          currentNumber++;
        }else{
          userTurn = false;
          gameOver = true;
        }
      }
      }

      
    }
    lastButtonState[i] = buttonPressed;
  }

  if(currentNumber>=NUM_BTNS){
    lcd.clear();
    lcd.setCursor(5, 1);
    lcd.print("Hai vinto");
    score ++;
    userTurn=false;
    currentNumber = 0;
    delay(500);
  }

}


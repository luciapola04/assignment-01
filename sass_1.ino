#include <LiquidCrystal_I2C.h>
#include <config.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4);
unsigned long lastSequenceTime = 0;   
const unsigned long sequenceInterval = 3000; 

void setup() { 
  pinMode(RED_PIN, OUTPUT);
  for (int i = 0; i<NUM_BTNS; i++) {
  	pinMode(btns_pin[i], INPUT);
  }
  Serial.begin(9600);
  randomSeed(analogRead(A4));
  lcd.init();   
  lcd.backlight(); 
  lcd.setCursor(5, 1);
  lcd.print("LET'S PLAY!");
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastSequenceTime >= sequenceInterval) {
    lastSequenceTime = currentMillis; 
    lcd.clear();
    lcd.setCursor(5, 1);
    lcd.print("Sequenza:");
    lcd.setCursor(7, 2);
    for (int i = 0; i < 4; i++) {
      int num = random(1, 5);
      lcd.print(num);
    }
  }
}


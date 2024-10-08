#include <pitches.h>

const int speakerPin = 8;
const int buttonPin = 4;
const int analogPin = A0;

int melody[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 
int noteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4}; // 4 = quarter note (四分音符), 8 = eighth note (八分音符)​
int noteDuration = 0;
int iterval = 0;

// （光敏）電阻數值
int sensorValue = 0;
// 按鈕
int buttonState = 0;
int lastButtonState = 0;
long lastDebounceTime = 0;
long debounceDelay = 5000;


//
int counter = 0;
void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);

}

void loop() {
  // 按鈕狀態
  int reading = digitalRead(buttonPin);
  // 得到可變電阻數值
  sensorValue = analogRead(analogPin);
  Serial.println(counter);
  // Serial.println(sensorValue);
  Serial.println(millis() - lastDebounceTime);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay && counter >= 10) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        Serial.println("按下五秒了");
        for (int i = 0; i < 10; i++) {
          tone(speakerPin, melody[i], 100);
          delay(1000);
        }
      }
    }
  } 
  if ((millis() - lastDebounceTime) > debounceDelay - 4500 && counter < 10) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        melody[counter] = sensorValue;
        counter++;
        Serial.print("新增旋律: ");
        Serial.println(sensorValue);
      }
    }
  }
  lastButtonState = reading;
  
  

}

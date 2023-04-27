#include <Arduino.h>

const int EN = 18;
const int  MOD = 5;
const int  PWM = 19;

void setup() {
  pinMode(EN,OUTPUT);
  pinMode(MOD,OUTPUT);
  pinMode(PWM,OUTPUT); 
}

void loop() {
    analogWrite(EN, 170);
    digitalWrite(PWM,HIGH);
    digitalWrite(MOD,HIGH);
}
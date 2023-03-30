#include <Arduino.h>

int fotodiode = A0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); 
}

void loop() {
int fotodiodeWaarde = analogRead(fotodiode);
  Serial.print("Fotodiode waarde: ");
  Serial.println(fotodiodeWaarde);
  delay(1000);
}
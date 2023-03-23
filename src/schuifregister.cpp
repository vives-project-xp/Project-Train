#include <Arduino.h>

int ioSelect =2;
int clockPulse=3;
int dataOut=4;
int value;

void setup() {
  pinMode(ioSelect,OUTPUT);
  pinMode(clockPulse,OUTPUT);
  pinMode(dataOut,INPUT);
  Serial.begin(9600);
}

void loop() {
  byte dataIn=0; //uint16_t or uint32_t voor meer inputs
  digitalWrite(ioSelect,0);//laat parallele input toe
  digitalWrite(clockPulse,0);//start klok pin laag
  digitalWrite(clockPulse,1);//clock pin laag, data zit in de IC
  digitalWrite(ioSelect,1);//schakel parallele input uit en zet seriele output aan

  for (int i = 0; i < 8; i++)//overloopt alle 8 de bits verhoog dit voor meer bits
  {
    value=digitalRead(dataOut);//data digitaal binnen lezen 
    Serial.print("waare");
    Serial.println(value);//waarde bit per bit weergeven 
    if (value){
      int a = (1<<i);//verschuift de bit achtereenvolgens naar de juiste plaats
      dataIn=dataIn|a;//combineert gegevens van verschoven bits om een ​​enkel 8-bits getal te vormen
    }
    digitalWrite(clockPulse,LOW);//achter dat elke bit binnen is clock puls geven voor volgende bit
    digitalWrite(clockPulse,HIGH);
  }
  
  Serial.print("dataIn DEC:");
  Serial.println(dataIn,DEC);//decimale waarde weergeven van dataIn
  Serial.print("dataIn BIN:");
  Serial.println(dataIn,BIN);//binaire waarde weergevan van dataIN
  delay(500);

}
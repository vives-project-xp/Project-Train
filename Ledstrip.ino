/*#include <FastLED.h>
#define NUM_LEDS 50
#define DATA_PIN 33
#define Color CRGB(255,139,23);
#define Brightness 25

CRGB leds[NUM_LEDS];
//#define ADCPin 36
//int incomingByte = 0; // for incoming serial data
//byte bits = 1;
const int typeLength = 7;
int downFlank = 0;
int upFlank = 0;
//int aantalLeds = 4;

int ioSelect =13;
int clockPulse = 14;
int dataOut=34;
int value;


void setup() {
  Serial.begin(115200); // opens serial port, sets data rate to 9600 bps
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
  pinMode(ioSelect,OUTPUT);
  pinMode(clockPulse,OUTPUT);
  pinMode(dataOut,INPUT);
  FastLED.setBrightness(Brightness);
}
void flanks(int value){
  if(value == 1){
  }
  else{
  for(int i = 0; i <= typeLength; i++){
  
    if(((value&0x2)>>1) > (value&0x1)){
      downFlank = i+1;
    }
    if(((value&0x2)>>1) < (value&0x1)){
      upFlank = i;
    }
    value = value>> 1;
    
    } 
  }
}
void ledStrip(){
 for(int i = upFlank;i < downFlank+1; i++)
        { 
        leds[i] = Color;
        FastLED.show();
        leds[i] = CRGB::Black;
        delay(150);
        }
 
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
    //Serial.print("waarde");
    //Serial.println(value);//waarde bit per bit weergeven 
    if (value){
      int a = (1<<i);//verschuift de bit achtereenvolgens naar de juiste plaats
      dataIn=dataIn|a;//combineert gegevens van verschoven bits om een ​​enkel 8-bits getal te vormen
    }
    digitalWrite(clockPulse,LOW);//achter dat elke bit binnen is clock puls geven voor volgende bit
    digitalWrite(clockPulse,HIGH);
  }
   flanks(dataIn);
   ledStrip();
   Serial.println(dataIn, BIN);

      
         
  
}*/



#include <FastLED.h>
#define NUM_LEDS 50
#define DATA_PIN 33
#define Color CRGB(255,139,23);
#define Brightness 25

CRGB leds[NUM_LEDS];
const int typeLength = 7;
int ioSelect = 13;
int clockPulse = 14;
int dataOut = 34;

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  pinMode(ioSelect, OUTPUT);
  pinMode(clockPulse, OUTPUT);
  pinMode(dataOut, INPUT);
  FastLED.setBrightness(Brightness);
}

void flanks(int value, int *startLed, int *endLed) {
  int ledCount = NUM_LEDS;
  for (int i = 0; i <= typeLength; i++) {
    if (((value & 0x2) >> 1) > (value & 0x1)) {
      *startLed = (int)(((float)i / (float)typeLength) * (float)ledCount);
    }
    if (((value & 0x2) >> 1) < (value & 0x1)) {
      *endLed = (int)(((float)i / (float)typeLength) * (float)ledCount);
    }
    value = value >> 1;
  }
}

void ledStrip(int startLed, int endLed) {
  for (int i = startLed; i <= endLed-1; i++) {
    leds[i] = Color;
  }
  FastLED.show();
  for (int i = startLed; i <= endLed; i++) {
    leds[i] = CRGB::Black;
  }
}

void loop() {
  int dataIn = 0;
  digitalWrite(ioSelect, 0);
  digitalWrite(clockPulse, 0);
  digitalWrite(clockPulse, 1);
  digitalWrite(ioSelect, 1);

  for (int i = 0; i < 8; i++) {
    int value = digitalRead(dataOut);
    if (value) {
      int a = (1 << i);
      dataIn = dataIn | a;
    }
    digitalWrite(clockPulse, LOW);
    digitalWrite(clockPulse, HIGH);
  }

  int startLed = 0;
  int endLed = NUM_LEDS - 1;
  flanks(dataIn, &startLed, &endLed);
  ledStrip(startLed, endLed);

  Serial.println(dataIn, BIN);
}

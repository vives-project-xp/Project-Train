#include <FastLED.h>
#define NUM_LEDS 400
#define DATA_PIN 33
#define Color CRGB(255,139,23);
#define Brightness 25
#define FadeDelay 20
#define PWMPin 3
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
  pinMode(PWMPin ,OUTPUT);
  
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

/*void ledStrip(int startLed, int endLed) {
  for (int i = startLed; i <= endLed; i++) {
    
    leds[i] = Color;
  }
  
  FastLED.show();
  delay(FadeDelay);
  for (int i = startLed; i <= endLed; i++) {
    
    leds[i] = CRGB::Black;
    delay(FadeDelay);
  }
}*/

void ledStrip(int startLed, int endLed) {
  // fade in
  for (int brightness = 0; brightness < Brightness; brightness++) {
    for (int i = startLed; i <= endLed; i++) {
      leds[i] = Color;
      leds[i].fadeToBlackBy(Brightness - brightness);
    }
    FastLED.show();
    delay(FadeDelay);
  }

  // fade out
  for (int brightness = Brightness; brightness >= 0; brightness--) {
    for (int i = startLed; i <= endLed; i++) {
      leds[i].fadeToBlackBy(brightness);
    }
    FastLED.show();
    delay(FadeDelay);
  }

  // turn off
  for (int i = startLed; i <= endLed; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}


void loop() {
   analogWrite(PWMPin,170);
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

  if (dataIn != 0) {
    int startLed = 0;
    int endLed = NUM_LEDS - 1;
    flanks(dataIn, &startLed, &endLed);
    ledStrip(startLed, endLed);
  }

  Serial.println(dataIn, BIN);
}

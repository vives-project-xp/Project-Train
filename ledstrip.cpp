#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 1
#define DATA_PIN 25
#define CLOCK_PIN 13

CRGB leds[NUM_LEDS];

void setup() { 
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
    }

void loop() { 
  // Turn the LED on, then pause
  leds[0] = CRGB(255, 139, 23);
  FastLED.show();
  delay(500);
  // Now turn the LED off, then pause
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(500);
}
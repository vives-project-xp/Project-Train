#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 30
#define DATA_PIN 25
#define fotodiode 25
#define Color CRGB(255,139,23);
#define Brightness 25
int aantalLeds = 4;

CRGB leds[NUM_LEDS];
void setup() { 
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
    Serial.begin(115200);
}
  
void loop()
{
FastLED.setBrightness(Brightness);
int diodeWaarde = digitalRead(fotodiode);
Serial.print("Fotodiode waarde: ");
Serial.println(diodeWaarde);
if(diodeWaarde == 1){
        for(int i = -aantalLeds;i < NUM_LEDS+1; i++)
        { 
        leds[i+aantalLeds] = Color;
        FastLED.show();
        leds[i] = CRGB::Black;
        delay(150);
        }
    }
          FastLED.clear();
   }
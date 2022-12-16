#include <FastLED.h>
#define LED_PIN 6 // plug in 6
#define NUM_LEDS 93
#define BRIGHTNESS 10
#define DELAY 200

CRGB leds[NUM_LEDS];
void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

}
void loop() {
  shipWheel1();
  delay(DELAY);
  FastLED.clear();
  
  // shipWheel3();
  // delay(DELAY);
  // FastLED.clear();

  shipWheel2();
  delay(DELAY);
  FastLED.clear();
  
}

void shipWheel1(){
  for (int i = 0; i < 32; i+=4) { // 24 LED ring
    leds[i] = CRGB(100, 100, 100);
  }
  for (int i = 32; i < 56; i++) { // 24 LED ring
    leds[i] = CRGB(100, 100, 100);
  }
  for (int i = 56; i < 72; i+=2) { // 16 LED ring 
    leds[i] = CRGB(100, 100, 100);
  }
  // for (int i = 72; i < 84; i+=3) { // 12 LED ring 
  //   leds[i] = CRGB(100, 100, 100);
  // }
  for (int i = 84; i < 92; i++) { // 8 LED ring
    leds[i] = CRGB(100, 100, 100);
  }
  // for (int i = 92; i < 93; i++) { // 1 LED ring -> Center
  // leds[i] = CRGB(100, 100, 100);
  // }
  FastLED.show();
}
void shipWheel2(){
  for (int i = 2; i < 32; i+=4) { // 24 LED ring
    leds[i] = CRGB(100, 100, 100);
  }
  for (int i = 32; i < 56; i++) { // 24 LED ring
    leds[i] = CRGB(100, 100, 100);
  }
  for (int i = 57; i < 72; i+=2) { // 16 LED ring 
    leds[i] = CRGB(100, 100, 100);
  }
  // for (int i = 73; i < 84; i+=2) { // 12 LED ring 
  //   leds[i] = CRGB(100, 100, 100);
  // }
  for (int i = 84; i < 92; i++) { // 8 LED ring
    leds[i] = CRGB(100, 100, 100);
  }
  // for (int i = 92; i < 93; i++) { // 1 LED ring -> Center
  // leds[i] = CRGB(100, 100, 100);
  // }
  FastLED.show();
}
void shipWheel3(){
  for (int i = 1; i < 32; i+=4) { // 24 LED ring
    leds[i] = CRGB(100, 100, 100);
  }
  for (int i = 32; i < 56; i++) { // 24 LED ring
    leds[i] = CRGB(100, 100, 100);
  }
  // for (int i = 57; i < 72; i+=2) { // 16 LED ring 
  //   leds[i] = CRGB(100, 100, 100);
  // }
  for (int i = 73; i < 84; i+=2) { // 12 LED ring 
    leds[i] = CRGB(100, 100, 100);
  }
  for (int i = 84; i < 92; i++) { // 8 LED ring
    leds[i] = CRGB(100, 100, 100);
  }
  // for (int i = 92; i < 93; i++) { // 1 LED ring -> Center
  // leds[i] = CRGB(100, 100, 100);
  // }
  FastLED.show();
}


void crossRotClock(){
  cross1();
  delay(DELAY);
  FastLED.clearData();
  FastLED.show();
  cross2();
  delay(DELAY);
  FastLED.clearData();
  FastLED.show();
  cross3();
  delay(DELAY);
  FastLED.clearData();
  FastLED.show();
  cross4();
  FastLED.show();
  delay(DELAY);
  FastLED.clearData();
}

void vortex() {
  for (int i = 0; i < 32; i++) { // 32 LED ring -> One color Circular progression clockwise
    leds[i] = CRGB(100, 100, 100);
    FastLED.show();
    delay(DELAY);
  }
  for (int i = 32; i < 56; i++) { // 24 LED ring -> One color Circular progression clockwise
    leds[i] = CRGB(100, 0, 0);
    FastLED.show();
    delay(DELAY);
  }
  for (int i = 56; i < 72; i++) { // 16 LED ring -> One color Circular progression clockwise
    leds[i] = CRGB(0, 100, 0);
    FastLED.show();
    delay(DELAY);
  }
  for (int i = 72; i < 84; i++) { // 12 LED ring -> One color Circular progression clockwise
    leds[i] = CRGB(0, 0, 100);
    FastLED.show();
    delay(DELAY);
  }
  for (int i = 84; i < 92; i++) { // 8 LED ring -> One color Circular progression clockwise
    leds[i] = CRGB(0, 0, 100);
    FastLED.show();
    delay(DELAY);
  }
  for (int i = 92; i < 93; i++) { // 1 LED ring -> Center
  leds[i] = CRGB(100, 100, 100);
  FastLED.show();
  delay(DELAY);
  }
}
void northSouth(){
  for(int i=0;i<93;i++){
    leds[0] = CRGB(100, 100, 100);
    leds[32] = CRGB(100, 100, 100);
    leds[56] = CRGB(100, 100, 100);
    leds[72] = CRGB(100, 100, 100);
    leds[84] = CRGB(100, 100, 100);
    leds[92] = CRGB(100, 100, 100);
    leds[93] = CRGB(100, 100, 100);
    leds[88] = CRGB(100, 100, 100);
    leds[78] = CRGB(100, 100, 100);
    leds[64] = CRGB(100, 100, 100);
    leds[44] = CRGB(100, 100, 100);
    leds[16] = CRGB(100, 100, 100);

    FastLED.show();
    delay(DELAY);
    }
}
void cross1(){
  for (int i = 0; i < 32; i+=8) { // 24 LED ring
    leds[i] = CRGB(100, 100, 100);
  }
  for (int i = 32; i < 56; i+=6) { // 24 LED ring
    leds[i] = CRGB(100, 100, 100);
  }
  for (int i = 56; i < 72; i+=4) { // 16 LED ring 
    leds[i] = CRGB(100, 100, 100);
  }
  for (int i = 72; i < 84; i+=3) { // 12 LED ring 
    leds[i] = CRGB(100, 100, 100);
  }
  for (int i = 84; i < 92; i+=2) { // 8 LED ring
    leds[i] = CRGB(100, 100, 100);
  }
  for (int i = 92; i < 93; i++) { // 1 LED ring -> Center
  leds[i] = CRGB(100, 100, 100);
  }
  FastLED.show();
}
void cross2(){
  for (int i = 2; i < 32; i+=8) { // 24 LED ring
    leds[i] = CRGB(100, 100, 100);
  }
  // for (int i = 32; i < 56; i+=6) { // 24 LED ring
  //   leds[i] = CRGB(100, 100, 100);
  // }
  for (int i = 57; i < 72; i+=4) { // 16 LED ring 
    leds[i] = CRGB(100, 100, 100);
  }
  // for (int i = 72; i < 84; i+=3) { // 12 LED ring 
  //   leds[i] = CRGB(100, 100, 100);
  // }
  // for (int i = 84; i < 92; i+=2) { // 8 LED ring
  //   leds[i] = CRGB(100, 100, 100);
  // }
  for (int i = 92; i < 93; i++) { // 1 LED ring -> Center
  leds[i] = CRGB(100, 100, 100);
  }
  FastLED.show();
}
void cross3(){
  for (int i = 4; i < 32; i+=8) { // 24 LED ring
    leds[i] = CRGB(100, 100, 100);
  }
  for (int i = 35; i < 56; i+=6) { // 24 LED ring
    leds[i] = CRGB(100, 100, 100);
  }
  for (int i = 58; i < 72; i+=4) { // 16 LED ring 
    leds[i] = CRGB(100, 100, 100);
  }
  // for (int i = 72; i < 84; i+=3) { // 12 LED ring 
  //   leds[i] = CRGB(100, 100, 100);
  // }
  for (int i = 85; i < 92; i+=2) { // 8 LED ring
    leds[i] = CRGB(100, 100, 100);
  }
  for (int i = 92; i < 93; i++) { // 1 LED ring -> Center
  leds[i] = CRGB(100, 100, 100);
  }
  FastLED.show();
}
void cross4(){
  for (int i = 6; i < 32; i+=8) { // 24 LED ring
    leds[i] = CRGB(100, 100, 100);
  }
  // for (int i = 35; i < 56; i+=6) { // 24 LED ring
  //   leds[i] = CRGB(100, 100, 100);
  // }
  for (int i = 59; i < 72; i+=4) { // 16 LED ring 
    leds[i] = CRGB(100, 100, 100);
  }
  // for (int i = 72; i < 84; i+=3) { // 12 LED ring 
  //   leds[i] = CRGB(100, 100, 100);
  // }
  // for (int i = 85; i < 92; i+=2) { // 8 LED ring
  //   leds[i] = CRGB(100, 100, 100);
  // }
  for (int i = 92; i < 93; i++) { // 1 LED ring -> Center
  leds[i] = CRGB(100, 100, 100);
  }
  FastLED.show();
}
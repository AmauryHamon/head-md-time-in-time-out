#include <FastLED.h>
#include <Wire.h>
#include <mpr121.h>

#define DATA_PIN A2
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS 93
#define POTENTIOMETER_PIN A3

// IMPORTANT: ONLY SET 15000 with DC OUTPUT 5V/15A, otherwise set to 500
#define MILLI_AMPS 15000

// #define DELAY 250
#define FRAMES_PER_SECOND 120  // here you can control the speed. With the Access Point / Web Server the animations run a bit slower.

CRGB leds[NUM_LEDS];
CRGB solidColor = CRGB::Blue;
uint8_t colorIndex[NUM_LEDS];




#include "Disk.h"

// Gradient palette "es_pinksplash_07_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/pink_splash/tn/es_pinksplash_07.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE(es_pinksplash_07_gp){
  0, 229, 1, 1,
  61, 242, 4, 63,
  101, 255, 12, 255,
  127, 249, 81, 252,
  153, 255, 11, 235,
  193, 244, 5, 68,
  255, 232, 1, 5
};

DEFINE_GRADIENT_PALETTE(algae_gp){
  0, 163, 241, 153,
  1, 161, 239, 149,
  3, 155, 235, 144,
  4, 153, 233, 142,
  5, 152, 231, 138,
  6, 148, 231, 137,
  7, 146, 229, 133,
  8, 144, 227, 132,
  9, 142, 225, 130,
  10, 139, 223, 127,
  11, 137, 221, 125,
  12, 135, 219, 122,
  13, 133, 217, 120,
  14, 130, 215, 117,
  15, 128, 213, 115,
  16, 126, 213, 114
};

DEFINE_GRADIENT_PALETTE(rain_gp){
  0, 213, 217, 226,
  1, 213, 215, 221,
  2, 210, 213, 219,
  3, 208, 211, 214,
  4, 206, 209, 210,
  5, 206, 207, 207,
  6, 203, 205, 203,
  7, 199, 201, 197,
  8, 199, 201, 197,
  9, 197, 197, 190,
  10, 194, 195, 188,
  11, 192, 193, 184,
  12, 190, 189, 182,
  13, 190, 187, 178,
  14, 188, 186, 176,
  15, 188, 186, 176,
  16, 188, 184, 172
};


DEFINE_GRADIENT_PALETTE(Caribbean_gp){
  0, 0, 0, 43,
  24, 0, 5, 85,
  36, 0, 10, 106,
  48, 1, 22, 130,
  60, 1, 32, 147,
  84, 1, 79, 138,
  97, 1, 91, 147,
  109, 3, 104, 156,
  121, 12, 104, 166,
  145, 35, 118, 176,
  157, 64, 118, 176,
  237, 184, 125, 26,
  237, 184, 125, 27,
  240, 206, 141, 25,
  242, 229, 149, 25,
  245, 242, 166, 24
};

CRGBPalette16 currentPalette(es_pinksplash_07_gp);
CRGBPalette16 targetPalette(Caribbean_gp);

CRGBPalette16 rainPal(rain_gp);





int key = 0;
int journeyStep = 0;
uint8_t whichPalette = 0;

bool touchHold = true;


void setup() {
  //Setup Wheelpad Capacitive Touch
  Serial.begin(19200);  //19200 works well for detecting capacitive touch somehow
  Wire.begin();
  CapaTouch.begin();

  //EXTRA RANDOMNESS!!!!!
  randomSeed(analogRead(0));

  //Setup LEDs
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

  FastLED.setDither(false);
  FastLED.setCorrection(TypicalLEDStrip);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, MILLI_AMPS);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  setupRings();

  //For blendPalette setup
  //fill the colorIndex array with random numbers
  for (int i = 0; i < NUM_LEDS; i++) {
    colorIndex[i] = random8();
  }

  FastLED.show();
}
void loop() {
  changeBrightness();  //Setup adjustable brightness
  touchControls();     //Setup controls on wheelpad Capacitive Touch


  FastLED.show();
  fadeToBlackBy(leds, NUM_LEDS, 10);
   Serial.println(whichPalette);
}
void changeBrightness() {
  //Adjust brightness with potentiometer
  int potentiometerValue = analogRead(POTENTIOMETER_PIN);
  int brightness = constrain(map(potentiometerValue, 33, 1023, 0, 255), 0, 255);
  // Serial.print(potentiometerValue);
  // Serial.print("\t");
  // Serial.println(brightness);
  FastLED.setBrightness(brightness);
}

//Setup wheelpad
void touchControls() {
  key = CapaTouch.wheelKey();
  bool newTouch = true;
  // Helper to check which case goes for which direction
  if (key >= 0) {
    // Serial.print("real key = ");
    Serial.println(key);
  } else {
    // Serial.println("-1");
  }
  switch (key) {
    case 9:  // North
      FastLED.clear();
      drawRadius360(0, CRGB::Yellow, 0, 5);


      if (!touchHold) {
        blendPalette();
        whichPalette++;
      }
      else {
      }
      break;
    case 5:  // West
      FastLED.clear();
      // shipWheel1a();
      drawRadius360(270, CRGB::Yellow, 0, 5);
      //If this is not hold, then do stepLess
      if (!touchHold) {
        stepLess();
      }
      break;
    case 13:  //  East
      FastLED.clear();
      // shipWheel1a();

      if (!touchHold) {
        stepMore();
        drawRadius360(90, CRGB::Yellow, 0, 5);
      }
      break;
    case 1:  // South
      FastLED.clear();
      blendPalette();
      if (!touchHold) {
        drawRadius360(180, CRGB::Yellow, 0, 5);
        whichPalette--;
      }
      else {
      }
      

      break;
    case 10:  // North North East
      FastLED.clear();
      // shipWheel1a();
      drawRadius360(22.5, CRGB::Yellow, 0, 5);
      break;

    case 11:  //  North East
      FastLED.clear();
      // shipWheel1a();
      drawRadius360(45, CRGB::Yellow, 0, 5);
      break;

    case 12:  //  East North East
      FastLED.clear();
      // shipWheel1a();
      drawRadius360(67.5, CRGB::Yellow, 0, 5);
      if (!touchHold) {
        stepMore();
      }
      break;

    
    case 14:  //  East South East
      FastLED.clear();
      // shipWheel1a();

      if (!touchHold) {
        stepMore();
        drawRadius360(90 + 22.5, CRGB::Yellow, 0, 5);
      }

      break;
    case 15:  //  South East
      FastLED.clear();
      // shipWheel1a();
      drawRadius360(90 + 45, CRGB::Yellow, 0, 5);
      // delay(DELAY);
      break;
    case 16:  //  South South East
      FastLED.clear();
      // shipWheel1a();
      drawRadius360(90 + 45 + 22.5, CRGB::Yellow, 0, 5);
      // delay(DELAY);
      break;
    case 2:  // South South West
      FastLED.clear();
      // shipWheel1a();
      drawRadius360(180 + 22.5, CRGB::Yellow, 0, 5);
      // delay(DELAY);
      break;
    case 3:  // South West
      FastLED.clear();
      // shipWheel1a();
      drawRadius360(270 - 45, CRGB::Yellow, 0, 5);
      // delay(DELAY);
      break;
    case 4:  // West South West
      FastLED.clear();
      // shipWheel1a();
      drawRadius360(270 - 22.5, CRGB::Yellow, 0, 5);
      if (!touchHold) {
        stepLess();
      }
      break;
    case 6:  // West North West
      FastLED.clear();
      // shipWheel1a();
      drawRadius360(360 - 45 - 22.5, CRGB::Yellow, 0, 5);
      if (!touchHold) {
        stepLess();
      }
      break;
    case 7:  // North West
      FastLED.clear();
      // shipWheel1a();
      drawRadius360(360 - 45, CRGB::Yellow, 0, 5);
      // delay(DELAY);
      break;
    case 8:  // North North West
      FastLED.clear();
      // shipWheel1a();
      drawRadius360(360 - 22.5, CRGB::Yellow, 0, 5);
      // delay(DELAY);
      break;
    case 20:  //Center button
      journeyStep = 0;
      Serial.print(journeyStep);
      break;
    default:  //release
      // delay(DELAY);
      newTouch = false;
      break;
  }
  switch (journeyStep) {
    case -1:
      journeyStep = 0;
      break;
    case 0:
      step0();
      break;
    case 1:
      step1();
      break;
    case 2:
      step2();
      break;
    case 3:
      step3();
      break;
    case 4:
      step4();
      break;
    case 5:
      step5();
      break;
    case 6:
      step6();
      break;
  }
  touchHold = newTouch;
}  // touchControls()
void stepLess() {
  // int DELAY = 250;
  // delay(DELAY);
  journeyStep--;
  journeyStep %= 7;
  // Serial.println(journeyStep);
}
void stepMore() {
  // int DELAY = 250;
  // delay(DELAY);
  journeyStep++;
  journeyStep %= 7;
  Serial.println(journeyStep);
}
void strandTest() {
  static uint8_t i = 0;
  EVERY_N_SECONDS(1) {
    i++;
    if (i >= NUM_LEDS)
      i = 0;
  }
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  leds[i] = solidColor;
}


//PING RADAR VIBE
void step0() {
  // pacifica_loop();
  EVERY_N_SECONDS(2) {
    setPixel360(0, 0, CRGB::White);
  }
  fadeToBlackBy(leds, NUM_LEDS, .2);
  // EVERY_N_MILLISECONDS(3000) {
  //   for(int i=0;i<=journeyStep;i++){
  //   setPixel360(random(360), i, CRGB::White);

  //   }
  // }
  // delay(10);
}
//CLEAR SKY SUNRISE
void step1() {

  pacifica_loop();
  setPixel360(0, 1, CRGB::White);
  // for(int i=0;i<2;i++){

  //   break;
  // }



  // EVERY_N_MILLISECONDS(100) {
  //   for(int i=0;i<=journeyStep;i++){
  //   setPixel360(random(360), i, CRGB::White);
  //   }
  // }
  fadeToBlackBy(leds, NUM_LEDS, 2);
}
//LIGHT RAIN, SUNNY GETTING CLOUDY
void step2() {
  pacifica_loop();
  setPixel360(0, 2, CRGB::White);

  // EVERY_N_MILLISECONDS(1000) {
  //   for(int i=0;i<=journeyStep;i++){
  //   setPixel360(random(360), i, CRGB::White);
  //   }
  // }
  fadeToBlackBy(leds, NUM_LEDS, 2);
}
//RAIN AND CLOUDY
void step3() {
  pacifica_loop();
  setPixel360(0, 3, CRGB::White);
  // EVERY_N_MILLISECONDS(100) {
  //   for(int i=0;i<=journeyStep;i++){
  //   setPixel360(random(360), i, CRGB::White);
  //   }
  // }
  fadeToBlackBy(leds, NUM_LEDS, 2);
}
//HEAVY RAIN AND LIGHTNING, DAY
void step4() {
  pacifica_loop();
  rainAnim();
  setPixel360(0, 4, CRGB::White);
  // EVERY_N_MILLISECONDS(100) {
  //   for(int i=0;i<=journeyStep;i++){
  //   setPixel360(random(360), i, CRGB::White);
  //   }
  // }
  fadeToBlackBy(leds, NUM_LEDS, 2);
}
//HEAVY RAIN AND LIGHTNING, DARK
void step5() {
  pacifica_loop();
  setPixel360(0, 5, CRGB::White);
  EVERY_N_MILLISECONDS(10000) {
    lightning();
  }
  EVERY_N_MILLISECONDS(100) {
    for (int i = 0; i <= journeyStep; i++) {
      setPixel360(random(360), i, CRGB::White);
    }
  }
  fadeToBlackBy(leds, NUM_LEDS, 2);
}
//STORM VORTEX RESET
void step6() {
  FastLED.clear();
  vortex();
  EVERY_N_MILLISECONDS(5000) {
    lightning();
  }
  fadeToBlackBy(leds, NUM_LEDS, 2);
}
//////////////////////////////////////////////////////////////
void shipWheel1a() {
  for (int i = 0; i < 32; i += 4) {  // 24 LED ring
    leds[i] = CRGB(100, 100, 100);
  }
  for (int i = 32; i < 56; i++) {  // 24 LED ring
    leds[i] = CRGB(100, 100, 100);
  }
  for (int i = 56; i < 72; i += 2) {  // 16 LED ring
    leds[i] = CRGB(100, 100, 100);
  }
  for (int i = 72; i < 84; i++) {  // 12 LED ring
    leds[i] = CRGB(100, 100, 100);
  }
  // for (int i = 84; i < 92; i++) { // 8 LED ring
  //   leds[i] = CRGB(100, 100, 100);
  // }
  // for (int i = 92; i < 93; i++) { // 1 LED ring -> Center
  // leds[i] = CRGB(100, 100, 100);
  // }
}

unsigned int dimmer = 1;
#define FLASHES 8
#define FREQUENCY 20  // delay between strikes

void lightning() {
  for (int flashCounter = 0; flashCounter < random8(3, FLASHES); flashCounter++) {
    if (flashCounter == 0) dimmer = 5;  // the brightness of the leader is scaled down by a factor of 5
    else dimmer = random8(1, 3);        // return strokes are brighter than the leader

    FastLED.showColor(CHSV(255, 0, 255 / dimmer));
    delay(random8(4, 10));  // each flash only lasts 4-10 milliseconds
    FastLED.showColor(CHSV(255, 0, 0));

    if (flashCounter == 0) delay(150);  // longer delay until next flash after the leader
    delay(50 + random8(100));           // shorter delay between strikes
  }
  delay(random8(FREQUENCY) * 100);  // delay between strikes
}

void blendPalette() {
  //color each pixel from the palette using the index from colorIndex[]
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette(currentPalette, colorIndex[i]);
  }
  nblendPaletteTowardPalette(currentPalette, targetPalette, 5);  //currentPalette to targetPalette, and speed
  switch (whichPalette) {
    case 0:
      targetPalette = algae_gp;
      break;
    case 1:
      targetPalette = rain_gp;
      break;
    case 2:
      targetPalette = Caribbean_gp;
      break;
  }
  if (whichPalette > 3) whichPalette = 0;
  EVERY_N_SECONDS(5) {
    // whichPalette++;
  }
  FastLED.show();
}
void rainAnim() {  //sparkling effect
  // Switch on a LED at random, choosing from random color from palette
  EVERY_N_MILLISECONDS(50) {
    leds[random8(0, NUM_LEDS - 1)] = ColorFromPalette(rainPal, random8(), 255, LINEARBLEND);
  }
  //Fade all LEDS down by 1 in Brightness each time this is called
  // fadeToBlackBy(leds, NUM_LEDS, 1); //rain style
  fadeToBlackBy(leds, NUM_LEDS, 10);  //heavy rain style
  // fadeToBlackBy(leds, NUM_LEDS, 100); //electrical sparks style


  FastLED.show();
}
void fadeall() {
  for (int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); }
}
void vortex() {
  static uint8_t hue = 0;
  Serial.print("x");
  // First slide the led in one direction

  for (int i = 0; i < NUM_LEDS; i++) {
    // Set the i'th led to red
    leds[i] = CHSV(hue++, 200, 63);  //removed hue++
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(50);
  }
  Serial.print("x");
}
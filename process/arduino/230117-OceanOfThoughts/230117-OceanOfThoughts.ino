#include <FastLED.h>
#include <Wire.h>
#include <mpr121.h>

#define DATA_PIN A2
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS 93
#define POTENTIOMETER_PIN A3
#define MILLI_AMPS 20000  // IMPORTANT: set the max milli-Amps of your power supply (4A = 4000mA)
// #define DELAY 250
#define FRAMES_PER_SECOND 120  // here you can control the speed. With the Access Point / Web Server the animations run a bit slower.

CRGB leds[NUM_LEDS];
CRGB solidColor = CRGB::Blue;
#include "Disk.h"

int key = 0;
int journeyStep = 0;
int paletteStep = 0;

bool touchHold = true;




//Setup wheelpad
void touchControls() {
  key = CapaTouch.wheelKey();
  bool newTouch = true;
  // Helper to check which case goes for which direction
  if (key >= 0) {
    // Serial.print("real key = ");
    Serial.println(key);
  }
  else {
    // Serial.println("-1");
  }
  switch (key) {
    case 9:  // North
      FastLED.clear();
      // shipWheel1a();
      drawRadius360(0, CRGB::Yellow, 0, 5);
      // delay(DELAY);
      break;
    case 10:  // North North East
      FastLED.clear();
      // shipWheel1a();
      drawRadius360(22.5, CRGB::Yellow, 0, 5);
      // delay(DELAY);
      break;
    case 11:  //  North East
      FastLED.clear();
      // shipWheel1a();
      drawRadius360(45, CRGB::Yellow, 0, 5);
      // delay(DELAY);
      break;
    case 12:  //  East North East
      FastLED.clear();
      // shipWheel1a();
      drawRadius360(67.5, CRGB::Yellow, 0, 5);
      if (!touchHold) {
        stepMore();
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
    case 1:  // South
      FastLED.clear();
      // shipWheel1a();
      drawRadius360(180, CRGB::Yellow, 0, 5);
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
    case 5:  // West
      FastLED.clear();
      // shipWheel1a();
      drawRadius360(270, CRGB::Yellow, 0, 5);
      //If this is not hold, then do stepLess
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
    case 20:  //Center
      // delay(DELAY);
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
  switch (paletteStep) {
    case -1:
      paletteStep = 4;
      break;
    case 0:

      break;
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
  }
  touchHold = newTouch;
}  // touchControls()

void setup() {
  //Setup Wheelpad Capacitive Touch
  Serial.begin(19200);  //19200 works well for detecting capacitive touch somehow
  Wire.begin();
  CapaTouch.begin();
  randomSeed(analogRead(0));  //EXTRA RANDOMNESS!!!!!

  //Setup LEDs
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

  FastLED.setDither(false);
  FastLED.setCorrection(TypicalLEDStrip);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, MILLI_AMPS);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  setupRings();
  FastLED.show();
}
void loop() {
  changeBrightness();  //Setup adjustable brightness
  touchControls();  //Setup controls on wheelpad Capacitive Touch

  // strandTest();
  FastLED.show();

  fadeToBlackBy(leds, NUM_LEDS, 10);
}

void changeBrightness() {
  //Adjust brightness with potentiometer
  int potentiometerValue = analogRead(POTENTIOMETER_PIN);
  Serial.print(potentiometerValue);
  Serial.print("\t");

  int brightness = constrain(map(potentiometerValue, 33, 1023, 0, 255),0,255);
  
  Serial.println(brightness); 
  FastLED.setBrightness(brightness);
  
}


void stepLess() {
  // int DELAY = 250;
  // delay(DELAY);
  journeyStep--;
  journeyStep %= 7;
  Serial.println(journeyStep);
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
  pacifica_loop();
  setPixel360(0, 0, CRGB::White);

  // EVERY_N_MILLISECONDS(3000) {
  //   for(int i=0;i<=journeyStep;i++){
  //   setPixel360(random(360), i, CRGB::White);

  //   }
  // }
  // delay(10);
  fadeToBlackBy(leds, NUM_LEDS, 2);
}
//CLEAR SKY SUNRISE
void step1() {

  pacifica_loop();
  setPixel360(0, 1, CRGB::White);
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

  EVERY_N_MILLISECONDS(100) {
    for (int i = 0; i < NUM_LEDS; i++) {
      // Set the i'th led to red
      static uint8_t hue = 0;
      leds[i] = CHSV(hue++, 255, 255);

      for (int i = 0; i <= journeyStep; i++) {
        setPixel360(random(360), i, CRGB::White);
        fadeToBlackBy(leds, NUM_LEDS, 50);
      }

      FastLED.show();
      fadeToBlackBy(leds, NUM_LEDS, 20);
      // delay(100);
    }
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
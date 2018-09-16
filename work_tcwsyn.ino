#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 3

#define NUM_LEDS 29

#define BRIGHTNESS 155

int wordNumber = 0;

int currentSelection = 4; // keeps track of word selected and starts with "computer"
int previousSelection = 0;

unsigned long timer = 5000; // wait 5 seconds before changing selection

//unsigned long timer = 86400000; // wait one day before changing selection

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);

byte neopix_gamma[] = {
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
  2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
  5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
  10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
  17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
  25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
  37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
  51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
  69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
  90, 92, 93, 95, 96, 98, 99, 101, 102, 104, 105, 107, 109, 110, 112, 114,
  115, 117, 119, 120, 122, 124, 126, 127, 129, 131, 133, 135, 137, 138, 140, 142,
  144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 167, 169, 171, 173, 175,
  177, 180, 182, 184, 186, 189, 191, 193, 196, 198, 200, 203, 205, 208, 210, 213,
  215, 218, 220, 223, 225, 228, 231, 233, 236, 239, 241, 244, 247, 249, 252, 255
};

const int words[][2] = {
  {  0, 3 },  //  1st LED position of the word  , last position of the word
  {  3, 13 },
  { 13, 17 },
  { 17, 21 },
  { 21, 25 },
  { 25, 29 }
};

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  testPattern();
  fullBlue(5);
}

void loop() {

  highlightWord(5);
  delay(timer);
}

void highlightWord(uint8_t wait) {

  if (currentSelection == previousSelection) {
    currentSelection = random(6);
  }

  //change previous word to blue
  for (uint16_t i = words[previousSelection][0]; i < words[previousSelection][1]; i++) {
    strip.setPixelColor(i, strip.Color(0, 255, 0, 0 ) );
    strip.show();
  }

  //change current word to white
  for (uint16_t i = words[currentSelection][0]; i < words[currentSelection][1]; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0, 255 ) );
    strip.show();
  }

  // select a new word for next time
  previousSelection = currentSelection;
  currentSelection = random(6);
}

void testPattern() {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0, 255 ) ); // R, G, B, W
    strip.setPixelColor(i - 1, strip.Color(0, 0, 0, 0 ) );
    strip.show();
    delay(10);
  }
  strip.setPixelColor(strip.numPixels() - 1, strip.Color(0, 0, 0, 0 ) );
  strip.show();
}

void fullBlue(uint16_t wait) {

  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 255, 0, 0 ) ); // R, G, B, W
  }
  strip.show();
  delay(wait);
}


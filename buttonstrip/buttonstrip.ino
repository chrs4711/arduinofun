
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_COUNT 10
#define LED_PIN 7
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// button stuff
const int BUTTON_ONE_PIN = 2;
const int BUTTON_TWO_PIN = 3;
const int LED_ONE = 10;
const int LED_TWO = 9;

int buttonOneState = 0;
int buttonTwoState = 0;

boolean oldState = HIGH;
int colorMode = 0;

void setup() {
  pinMode(LED_ONE, OUTPUT);
  pinMode(LED_TWO, OUTPUT);

  pinMode(BUTTON_ONE_PIN, INPUT_PULLUP);
  pinMode(BUTTON_TWO_PIN, INPUT_PULLUP);

  strip.begin();
  strip.setBrightness(64); // 31, 63, 95, 127, 159, 191, 223, 255
  strip.show();

  bootSequence();
}

void loop() {

  boolean newState = digitalRead(BUTTON_ONE_PIN);

  if ((newState == LOW) && (oldState == HIGH)) {

    delay(20);

    newState = digitalRead(BUTTON_ONE_PIN);

    if (newState == LOW) {
      switchModeNow();
    }
  }

  oldState = newState;
}

void switchModeNow() {

  if (++colorMode > 6)
    colorMode = 0;

  switch (colorMode) {
    case 0:
      justColor(strip.Color(0, 0, 255));
      break;
    case 1:
      justColor(strip.Color(0, 255, 0));
      break;
    case 2:
      justColor(strip.Color(0, 255, 255));
      break;
    case 3:
      justColor(strip.Color(255, 0, 0));
      break;
    case 4:
      justColor(strip.Color(255, 0, 255));
      break;
    case 5:
      justColor(strip.Color(255, 255, 0));
      break;
    case 6:
      justColor(strip.Color(255, 255, 255));
      break;
  }
}

void justColor(uint32_t color) {
  strip.fill(color);
  strip.show();
}

void bootSequence() {

  strip.clear();

  uint32_t color = strip.Color(127, 0, 127);

  up(color);
  down(color);
  strip.clear();
  strip.show();
}

// Run a pixel up the strip!
void up(uint32_t color) {

  strip.clear();

  for (int i = 0; i < strip.numPixels(); i++) {
    blink(i, color, 50);
  }
}

// Run a pixel down the strip!
void down(uint32_t color) {

  strip.clear();

  for (int i = strip.numPixels() - 1; i >= 0; i--) {
    blink(i, color, 50);
  }
}

// Blink a pixel with a color!
void blink(int pixel, uint32_t color, int dur) {

  strip.setPixelColor(pixel, color);
  strip.show();

  delay(50);

  strip.clear();
}

// not needed, about to be deleted :-D
// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
// stolen from the neopixel examples
// void rainbow(int wait) {
//   // Hue of first pixel runs 5 complete loops through the color wheel.
//   // Color wheel has a range of 65536 but it's OK if we roll over, so
//   // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
//   // means we'll make 5*65536/256 = 1280 passes through this outer loop:
//   for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
//     for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
//       // Offset pixel hue by an amount to make one full revolution of the
//       // color wheel (range of 65536) along the length of the strip
//       // (strip.numPixels() steps):
//       int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
//       // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
//       // optionally add saturation and value (brightness) (each 0 to 255).
//       // Here we're using just the single-argument hue variant. The result
//       // is passed through strip.gamma32() to provide 'truer' colors
//       // before assigning to each pixel:
//       strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
//     }
//     strip.show(); // Update strip with new contents
//     delay(wait);  // Pause for a moment
//   }
// }

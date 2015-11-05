#include <Adafruit_NeoPixel.h>

unsigned long lastTime = 0;

// MS to wait to debounce a button press.
const unsigned long buttonDuration = 500;

// Number of functions that have been defined;
const unsigned short NUM_FUNCTIONS = 6;
unsigned short state = 0;
void (*functions[NUM_FUNCTIONS])(void);


#define PIXEL_PIN    12    // Digital IO pin connected to the NeoPixels.

#define PIXEL_COUNT 15

// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  functions[0] = turnOnBlack;
  functions[1] = turnOnPink;
  functions[2] = turnOnBlue;
  functions[3] = turnOnWhite;
  functions[4] = rainbow;
  functions[5] = scanner;
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(0, buttonPressed, FALLING);
  turnOnBlack();
  strip.begin();
  Serial.begin(57600);
}

void buttonPressed() {
  unsigned long currentTime = millis();
  if (currentTime < lastTime) {
    //Handle roll over in millis counter.
    lastTime = 0;
  }
  if ( (currentTime - lastTime) < buttonDuration) {
    return;
  }
  lastTime = currentTime;
  state++;
  if (state > NUM_FUNCTIONS) {
    state = 0;
  }
}

void loop() {
  (*functions[state])();
}

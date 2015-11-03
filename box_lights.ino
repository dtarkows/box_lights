#include <Adafruit_NeoPixel.h>



unsigned long lastTime = 0;

// MS to wait to debounce a button press.
const unsigned long buttonDuration = 500;

// Number of functions that have been defined;
const unsigned short NUM_FUNCTIONS = 5;
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
  functions[0] = turnOff;
  functions[1] = turnOnPink;
  functions[2] = turnOnBlue;
  functions[3] = white;
  functions[4] = rainbow;
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(0, buttonPressed, FALLING);
  turnOff();
  strip.begin();
}

void setColor(uint8_t red, uint8_t green, uint8_t blue) {
  for (int i = 0; i < PIXEL_COUNT; i++) {
    strip.setPixelColor(i, red, green, blue);
  }
  strip.show();
}
void turnOnPink(void) {
  setColor(255, 20, 147);
}

void turnOnBlue(void) {
  setColor(0, 0, 255);
}

void turnOff(void) {
  for (int i = 0; i < PIXEL_COUNT; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
}
void white(void) {
  for (int i = 0; i < PIXEL_COUNT; i++) {
    strip.setPixelColor(i, strip.Color(255, 255, 255));
  }
  strip.show();
} 

void rainbow(void) {
  uint16_t i;

  for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, Wheel((i * 256 / strip.numPixels())));
  }
  strip.show();
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
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

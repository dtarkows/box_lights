unsigned long lastUpdateTime = 0;
unsigned short pixelIndex = 0;
short direction = 1;

// Make it take one minute to move through the strip.
const unsigned long stripDuration = 30*1000;

void scanner(void) {

  // On the first update turn the first pixel on.
  if (lastUpdateTime == 0) {
    strip.setPixelColor(0, 255, 255, 255);
    for (int i = 1; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, 0, 0, 0);
    }
    strip.show();
    lastUpdateTime = millis();
    return;
  }

  unsigned long timeSinceLastUpdate = millis() - lastUpdateTime;

  unsigned long durationPerPixel = stripDuration/strip.numPixels();
  
  // Check if it is time to move to the next pixel.
  if (timeSinceLastUpdate >= durationPerPixel) {

    // Move to the next pixel and reset the last update time.
    pixelIndex += direction;
    lastUpdateTime = millis();
    timeSinceLastUpdate = 0;

    // Check to see if we are at the end of the strip.
    if ( (pixelIndex == 0) || (pixelIndex == (strip.numPixels() -1)) ) {
      direction = -direction;
    }
  }
  
  float durationFraction = static_cast<float>(timeSinceLastUpdate) / static_cast<float>(durationPerPixel);
  unsigned short mainPixelBrightness = 255 * (1.0 - durationFraction);
  unsigned short nextPixelBrightness = 255 * durationFraction;

  // Turn everything off
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 0, 0, 0);
  }

  // Set the main pixel
  strip.setPixelColor(pixelIndex, mainPixelBrightness, mainPixelBrightness, mainPixelBrightness);
  
  // Set the next pixel brightness
  strip.setPixelColor(pixelIndex + direction, nextPixelBrightness, nextPixelBrightness, nextPixelBrightness);
  strip.show();
}


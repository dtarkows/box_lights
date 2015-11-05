void turnOnPink(void) {
  setColor(255, 20, 147);
}
void turnOnBlue(void) {
  setColor(0, 0, 255);
}

void turnOnWhite(void) {
  setColor(255,255,255);
}

void turnOnBlack(void) {
  setColor(0,0,0);
}

void setColor(uint8_t red, uint8_t green, uint8_t blue) {
  for (int i = 0; i < PIXEL_COUNT; i++) {
    strip.setPixelColor(i, red, green, blue);
  }
  strip.show();
}



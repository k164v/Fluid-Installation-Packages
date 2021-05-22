/**
   Function used for color interplation
*/
void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void updateLedColorBasedOnHTML() {
  colorWipe(strip.Color(a_color[1],   a_color[0],   a_color[2]), delayTime); // Red
  if (isMove) {
    colorWipe(strip.Color(b_color[1],   b_color[0],   b_color[2]), delayTime); // Green
  }
}


void getLEDReady(){
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(150);
}

#include "DigiKeyboard.h"
#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN 1
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixel.begin();
  pixel.show();
  pixel.setBrightness(40);
  pixelWrite(255,0,0);
  //DigiKeyboard.delay(2000);
  if (digitalRead(0)) {
    return; // don't activate
    pixelWrite(0,255,0);
  }
  
  // don't need to set anything up to use DigiKeyboard
  DigiKeyboard.delay(500);
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
  DigiKeyboard.delay(600);
  //DigiKeyboard.print("https://youtu.be/dQw4w9WgXcQ?t=43s");
  DigiKeyboard.print("https://youtu.be/dQw4w9WgXcQ");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(2000);
  DigiKeyboard.sendKeyStroke(KEY_SPACE);
//  DigiKeyboard.sendKeyStroke(KEY_F11);
}

void pixelWrite(int r, int g, int b) {
  pixel.setPixelColor(0, pixel.Color(r, g, b));
  pixel.show();
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    pixel.setPixelColor(i, Wheel((i+j) & 255));
    pixel.show();
    DigiKeyboard.delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixel.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixel.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixel.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void loop() {        
  rainbow(20);  
}

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
  #define PSTR // Make Arduino Due happy
#endif

#define PIN 13

// MATRIX DECLARATION: (Your original setup is perfect)
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_TOP    + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB           + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };

// --- New global variables ---
int r = 0;       // Current radius of the circle
int pass = 0;    // Current color index (re-using your variable name)
int centerX;     // Center X coordinate (will be set in setup)
int centerY;     // Center Y coordinate (will be set in setup)

void setup() {
  matrix.begin();
  matrix.setBrightness(40);
  
  // Calculate the center of the matrix
  // For an 8x8 matrix, this will set (centerX, centerY) to (3, 3)
  centerX = matrix.width() / 2 - 1;
  centerY = matrix.height() / 2 - 1;
}

void loop() {
  matrix.fillScreen(0); // Clear the screen for the next frame

  // Draw a circle at the center with the current radius 'r'
  // and the current color from the 'colors' array
  matrix.drawCircle(centerX, centerY, r, colors[pass]);

  matrix.show(); // Update the display
  delay(100);    // Controls the speed of the ripple

  r++; // Increase the radius for the next frame

  // If the radius is larger than the matrix, reset it
  // and move to the next color.
  // 8 is a good value for an 8x8 matrix.
  if (r > 8) { 
    r = 0; // Reset radius
    
    // Cycle to the next color
    if (++pass >= 3) {
      pass = 0;
    }
  }
}
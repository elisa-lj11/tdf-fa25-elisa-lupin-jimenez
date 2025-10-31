/*
Ripple-effect-v7

Authors: Elisa Lupin-Jimenez, Tala Salman

Calls OpenMeteo's Marine Weather API (https://open-meteo.com/en/docs/marine-weather-api) to
fetch a coordinate's wave height, period, and direction, then visualizes this data in the form
of a ripple moving across a NeoPixel LED matrix.

  - Wave height = Backdrop color (red is short wave, purple is tall wave)
  - Wave period = New ripple generated at 5x speed (e.g., wave period of 5 seconds means one
  ripple per second)
  - Wave direction = Tracks 8 directional movements (direction from which wave comes)
    - North
    - West
    - East
    - South
    - Northwest
    - Northeast
    - Southwest
    - Southeast

Code-assist with Gemini:
  - https://gemini.google.com/share/952c75304788
  - https://gemini.google.com/share/a1fae9ae0fa8
  - https://gemini.google.com/share/bca992c6a043
  - https://gemini.google.com/share/3eb1af5be35b
  - https://gemini.google.com/share/6cacdb4dc85b
*/

#include <secrets.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
  #define PSTR // Store strings in flash memory instead of data memory
#endif

#define PIN 13 // Which pin NeoPixel matrix is plugged into

// ---------- WiFi credentials ----------
const char* ssid = SECRET_SSID;
const char* password = SECRET_PASSWORD;


// ---------- Variables ----------
const int ROWS = 8; // Number of pixels in row
const int COLS = 8; // Number of pixels in column
const int BRIGHTNESS = 5; // Brightness of NeoPixel

// These globals store the data from the API
int currentDir = -1;     // ⭐ start as invalid
double currentPeriod = 0;
double currentHeight = 0;

unsigned long lastUpdate = 0;
const unsigned long updateInterval = 60 * 1000 * 10; // refresh every 10 min to avoid http.GET() freeze

// MATRIX DECLARATION:
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(ROWS, COLS, PIN,
  NEO_MATRIX_TOP   + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG, // (0,0) is TOP-RIGHT
  NEO_GRB          + NEO_KHZ800);

// ---------- Location (Near Golden Gate Bridge) ----------
const double latitude = 37.8199;
const double longitude = -122.4783;

// ---------- Location (Steamer Lane in Santa Cruz) ----------
// const double latitude = 36.951981;
// const double longitude = -122.026527;

// ---------- Location (Nazare in Portugal) ----------
// const double latitude = 39.600274;
// const double longitude = -9.074325;

// ---------- Location (Banzai Pipeline in Hawaii) ----------
// const double latitude = 21.664227;
// const double longitude = -158.051616;

// ---------- Location (Amchit in Lebanon) ----------
// const double latitude = 34.141191;
// const double longitude = 35.630157;

// ---------- Location (Bocas del Toro in Panama) ----------
// const double latitude = 9.395276;
// const double longitude = -82.241983;

// ---------- Location (Pacific Beach in San Diego) ----------
// const double latitude = 32.795781;
// const double longitude = -117.256979;

// ---------- Location (Uluwatu in Indonesia) ----------
// const double latitude = -8.828042;
// const double longitude = 115.085059;

// ---------- Open-Meteo Marine Weather API ----------
String wave_api = "https://marine-api.open-meteo.com/v1/marine?latitude="
                  + String(latitude, 6)
                  + "&longitude="
                  + String(longitude, 6)
                  + "&current="
                  + "wave_direction,"
                  + "wave_period,"
                  + "wave_height";

// --- New Globals for Ripple Management ---

// This struct will hold the state of a single ripple (wave)
struct Ripple {
  int pos;       // x, y, (x+y), or (x-y) coordinate, depending on direction
  uint16_t color;  // Color of this ripple
  bool active = false; // Is this ripple currently on-screen?
  int direction; // Stores the snapped visual direction (0, 45, 90, 135, 180, 225, 270, 315)
};

#define MAX_RIPPLES 5 // Max simultaneous ripples we can track
Ripple ripples[MAX_RIPPLES]; // The array to hold all our ripples

unsigned long lastRippleTime = 0; // When the last ripple was spawned
unsigned long currentPeriodInMillis = 3000; // Stores the period

// --- Helper Functions ---

/**
 * @brief Connects the ESP32 to WiFi
 */
void connectToWiFi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi connected!");
}

/**
 * @brief Fetches the wave data from the OpenMeteo Marine Weather API
 */
void getWaveData() {
  Serial.print("Requesting: ");
  Serial.println(wave_api);

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(wave_api);
    int httpResponseCode = http.GET();

    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);

    if (httpResponseCode == 200) {
      String payload = http.getString();
      JSONVar jsonObject = JSON.parse(payload);

      if (JSON.typeof(jsonObject) == "undefined") {
        Serial.println("Parsing input failed!");
        currentDir = -1;    // ⭐ invalidate reading
        http.end();
        return;
      }

      // Read all values from the JSON
      currentDir = double(jsonObject["current"]["wave_direction"]);
      currentPeriod = double(jsonObject["current"]["wave_period"]);
      currentHeight = double(jsonObject["current"]["wave_height"]); 

      Serial.print("Wave direction: ");
      Serial.print(currentDir);
      Serial.println("°");
      Serial.print("Wave period: ");
      Serial.print(currentPeriod);
      Serial.println(" seconds");
      Serial.print("Wave height: ");
      Serial.println(currentHeight);
    } else {
      Serial.print("HTTP error: ");
      Serial.println(httpResponseCode);
      currentDir = -1;    // ⭐ invalidate reading
    }
    http.end();
  } else {
    Serial.println("WiFi disconnected. Reconnecting...");
    WiFi.reconnect();
    currentDir = -1;    // ⭐ invalidate reading
  }
}

/**
 * @brief
 * Snaps a raw angle (0-360) from the API to one of 8
 * visual directions for our drawing logic.
 *
 * API Directions (direction wave comes from):
 * 0=E, 45=NE, 90=N, 135=NW, 180=W, 225=SW, 270=S, 315=SE
 * @param dir The direction received from the API call
 */
int snapDirection(int dir) {
  // This logic maps API direction to the correct visual case.
  // Each slice is 45 degrees wide.
if (dir > 337.5 || dir <= 22.5) { // API is NORTH (0)
    return 0; // Return visual WEST (case 180)
  } else if (dir > 22.5 && dir <= 67.5) {   // API is NORTHEAST (45)
    return 45; // Return visual NORTHWEST (case 135)
  } else if (dir > 67.5 && dir <= 112.5) { // API is EAST (90)
    return 90;  // Return visual NORTH (case 90)
  } else if (dir > 112.5 && dir <= 157.5) { // API is SOUTHEAST (135)
    return 135; // Return visual NORTHEAST (case 45)
  } else if (dir > 157.5 && dir <= 202.5) { // API is SOUTH (180)
    return 180; // Return visual EAST (case 0)
  } else if (dir > 202.5 && dir <= 247.5) { // API is SOUTHWEST (225)
    return 225; // Return visual SOUTHEAST (case 315)
  } else if (dir > 247.5 && dir <= 292.5) { // API is WEST (270)
    return 270; // Return visual SOUTH (case 270)
  } else { // (dir > 292.5 && dir <= 337.5) // API is NORTHWEST (315)
    return 315; // Return visual SOUTHWEST (case 225)
  }
}

/**
 * @brief
 * Visualizes the ripple moving across the matrix.
 * It's called continuously from the main loop.
 * It manages spawning, updating, and drawing all ripples.
 * @param dir Wave direction
 * @param period Wave period
 * @param height Wave height
 */
void visualizeRipple(int dir, double period, double height) {
  int snappedDir = snapDirection(dir);

  period /= 5; // Make period 5 times as fast for better visual effect

  // Update global settings for ripple logic
  currentPeriodInMillis = (unsigned long)(period * 1000.0);

  // Prevent divide-by-zero or spamming if period is 0
  if (currentPeriodInMillis == 0) {
    currentPeriodInMillis = 1000; // Default to 1 second
  }

  unsigned long currentTime = millis();

  // 1. Check if it's time to spawn a new ripple
  if (currentTime - lastRippleTime >= currentPeriodInMillis) {
    addNewRipple(snappedDir, height); // Use snappedDir
    lastRippleTime = currentTime; // Reset the timer
  }

  // 2. Update positions of all active ripples
  updateRipples();

  // 3. Draw all ripples to the buffer
  // Calculate background color based on height.
  // Map height from 0.0 (Red) through the spectrum to 3.0 (Purple)
  double constrainedHeight = constrain(height, 0.0, 3.0);
  double fraction = constrainedHeight / 3.0; // 0.0 (low) to 1.0 (high)

  // Map the 0.0-1.0 fraction to a hue range (0-65535).
  // Hue 0 is Red.
  // Hue ~48000 is a nice Purple/Violet.
  // This will naturally pass through Orange, Yellow, Green, Cyan, and Blue.
  uint16_t hue = (uint16_t)(fraction * 48000.0);
  uint8_t saturation = 255; // Full saturation for rich color
  uint8_t value = 100;       // Dim brightness (0-255)

  // Convert HSV color to the 16-bit packed color
  uint16_t backdropColor = matrix.ColorHSV(hue, saturation, value);
  
  matrix.fillScreen(backdropColor); // Use the new dynamic color
  
  drawRipples(); // Draw ripples on top

  // 4. Show the new frame
  matrix.show();
}

/**
 * @brief
 * Finds an inactive ripple in the array and spawns it at the correct edge.
 * @param snappedDir The visual direction (0, 45, 90, 135, 180, 225, 270, 315)
 * @param height The wave height (used for color)
 */
void addNewRipple(int snappedDir, double height) {
  for (int i = 0; i < MAX_RIPPLES; i++) {
    if (!ripples[i].active) { // Found a free slot
      ripples[i].active = true;
      ripples[i].direction = snappedDir; // Store the direction

      // 1. Set start position based on direction
      // (0,0) is TOP-RIGHT. x=0 is Right, x=7 is Left. y=0 is Top, y=7 is Bottom.
      int w_idx = matrix.width() - 1;  // 7 (max x index)
      int h_idx = matrix.height() - 1; // 7 (max y index)
      
      switch (snappedDir) { 
        case 0:   // Visual East (moves Left, x: 7->0)
          ripples[i].pos = w_idx; // x = 7 (Left)
          break;
        case 180: // Visual West (moves Right, x: 0->7)
          ripples[i].pos = -1; // x = 0 (Right)
          break;
        case 90:  // Visual North (moves Down, y: 7->0)
          ripples[i].pos = h_idx; // y = 7 (Bottom)
          break;
        case 270: // Visual South (moves Up, y: 0->7)
          ripples[i].pos = -1; // y = 0 (Top)
          break;
        case 45:  // Visual NE (moves Bottom-Left, k=x+y: 14->0)
          // Starts at SW corner (x=7, y=7)
          ripples[i].pos = w_idx + h_idx; // pos = 14
          break;
        case 225: // Visual SW (moves Top-Right, k=x+y: 0->14)
          // Starts at NE corner (x=0, y=0)
          ripples[i].pos = -1; // pos = 0
          break;
        case 135: // Visual NW (moves Bottom-Right, k=x-y: -7->7)
          // Starts at SE corner (x=0, y=7)
          ripples[i].pos = 0 - h_idx; // pos = -7
          break;
        case 315: // Visual SE (moves Top-Left, k=x-y: 7->-7)
          // Starts at NW corner (x=7, y=0)
          ripples[i].pos = w_idx; // pos = 7
          break;
      }
      
      // Set ripple color to a constant white
      ripples[i].color = matrix.Color(255, 255, 255); 
      
      return; // Exit after spawning one ripple
    }
  }
}

/**
 * @brief
 * Updates the position of all active ripples.
 */
void updateRipples() {
  for (int i = 0; i < MAX_RIPPLES; i++) {
    if (ripples[i].active) {
      bool deactivating = false;
      int moveDir = ripples[i].direction;
      int w_idx = matrix.width() - 1;  // 7
      int h_idx = matrix.height() - 1; // 7
      
      // 1. Move the ripple
      // (0,0) is top-right. X+ is LEFT. Y+ is DOWN.
      switch (moveDir) { 
        case 0:   // Visual East (moving left, x: 7->0)
          ripples[i].pos--; 
          if (ripples[i].pos < 0) deactivating = true;
          break;
        case 180: // Visual West (moving right, x: 0->7)
          ripples[i].pos++; 
          if (ripples[i].pos > w_idx) deactivating = true;
          break;
        case 90:  // Visual North (moving up, y: 7->0)
          ripples[i].pos--; 
          if (ripples[i].pos < -1) deactivating = true;
          break;
        case 270: // Visual South (moving down, y: 0->7)
          ripples[i].pos++; 
          if (ripples[i].pos > h_idx) deactivating = true;
          break;
        case 45:  // Visual NE (moves Top-Right, k=x+y: 14->0)
          ripples[i].pos--;
          if (ripples[i].pos < 0) deactivating = true;
          break;
        case 225: // Visual SW (moves Bottom-Left, k=x+y: 0->14)
          ripples[i].pos++;
          if (ripples[i].pos > (w_idx + h_idx)) deactivating = true;
          break;
        case 135: // Visual NW (moves Top-Left, k=x-y: -7->7)
          ripples[i].pos++;
          if (ripples[i].pos > w_idx) deactivating = true;
          break;
        case 315: // Visual SE (moves Bottom-Right, k=x-y: 7->-7)
          ripples[i].pos--;
          if (ripples[i].pos < -h_idx) deactivating = true;
          break;
      }

      // 2. Deactivate if it's off-screen
      if (deactivating) {
        ripples[i].active = false;
      }
    }
  }
}

/**
 * @brief
 * Draws all active ripples to the matrix buffer with slight variations.
 */
void drawRipples() {
  for (int i = 0; i < MAX_RIPPLES; i++) {
    if (ripples[i].active) {
      int drawDir = ripples[i].direction;
      uint16_t color = ripples[i].color;
      int mainPos = ripples[i].pos; // The main coordinate (or 'k' value) for the line
      int maxCoord = max(ROWS, COLS) - 1; // Max index (7 for 8x8 matrix)

      switch (drawDir) {
        case 90:  // North (moving up, horizontal line)
        case 270: // South (moving down, horizontal line)
          // `mainPos` is the Y-coordinate. We vary the Y-coordinate slightly.
          for (int x = 0; x <= maxCoord; x++) {
            int wobble = random(0, 2); // 0 or 1
            int variedY = constrain(mainPos + wobble, 0, maxCoord);
            matrix.drawPixel(x, variedY, color);
          }
          break;
          
        case 0:   // East (moving right, vertical line)
        case 180: // West (moving left, vertical line)
          // `mainPos` is the X-coordinate. We vary the X-coordinate slightly.
          for (int y = 0; y <= maxCoord; y++) {
            int wobble = random(0, 2); // 0 or 1
            int variedX = constrain(mainPos + wobble, 0, maxCoord);
            matrix.drawPixel(variedX, y, color);
          }
          break;

        // These draw diagonal lines of the type k = x + y
        case 45:  // NE
        case 225: // SW
          // `mainPos` is 'k' in the line equation y = k - x.
          // We iterate over x and find the y, wobbling 'k' slightly.
          for (int x = 0; x <= maxCoord; x++) {
            int wobble = random(0, 2); // 0 or 1
            int variedK = mainPos + wobble; // Wobble the 'k' value
            int y = variedK - x;
            if (y >= 0 && y <= maxCoord) { // Draw if on-screen
              matrix.drawPixel(x, y, color);
            }
          }
          break;

        // These draw diagonal lines of the type k = x - y
        case 135: // NW
        case 315: // SE
          // `mainPos` is 'k' in the line equation y = x - k.
          // We iterate over x and find the y, wobbling 'k' slightly.
          for (int x = 0; x <= maxCoord; x++) {
            int wobble = random(0, 2); // 0 or 1
            int variedK = mainPos + wobble; // Wobble the 'k' value
            int y = x - variedK;
            if (y >= 0 && y <= maxCoord) { // Draw if on-screen
              matrix.drawPixel(x, y, color);
            }
          }
          break;
      }
    }
  }
}

// ---------- Setup ----------
void setup() {
  Serial.begin(9600);
  while (!Serial); 
  delay(100); 
  Serial.println("Serial connection established.");

  matrix.begin();
  matrix.setBrightness(BRIGHTNESS);
  matrix.show(); // Initialize matrix to off
  Serial.println("Matrix initialized.");

  // === HARDWARE TEST ===
  Serial.println("Starting hardware test...");
  // (0,0) is TOP-RIGHT
  matrix.drawPixel(0, 0, matrix.Color(255, 0, 0)); 
  matrix.show(); // Show the pixel
  Serial.println("Hardware test: Red pixel at (0,0) [TOP-RIGHT] should be on for 2 sec.");
  delay(2000); // Wait 2 seconds
  matrix.fillScreen(0); // Clear screen
  matrix.show();
  Serial.println("Hardware test complete.");
  // ===================

  connectToWiFi();
  delay(100); 
  getWaveData();    // initial fetch

  // Initialize all ripples to inactive
  for (int i = 0; i < MAX_RIPPLES; i++) {
    ripples[i].active = false;
  }
  
  lastRippleTime = millis(); // Set initial- spawn time
}

// ---------- Main Loop ----------
void loop() {
  if (millis() - lastUpdate > updateInterval) {
    getWaveData();
    lastUpdate = millis();
  }

  // ⭐ Only show light if wave direction is valid
  if (currentDir != -1) {
    visualizeRipple(currentDir, currentPeriod, currentHeight);
  } else {
    matrix.fillScreen(0); // Clear the screen
    matrix.show();      
  }

  // Add delay for animation frame rate
  delay(100); // ~10 frames per second
}
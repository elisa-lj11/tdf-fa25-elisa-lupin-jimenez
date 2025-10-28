/*
Ripple-effect-v2
Switched back to (randomly varied) straight line
Vibe-coded with Gemini: https://gemini.google.com/share/a1fae9ae0fa8
Fixed with Gemini!
*/

#include <secrets.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
  #define PSTR // Make Arduino Due happy
#endif

#define PIN 13 // Which pin NeoPixel matrix is plugged into

// ---------- WiFi credentials ----------
const char* ssid = SECRET_SSID;
const char* password = SECRET_PASSWORD;


// ---------- Variables ----------
const int ROWS = 8; // Number of pixels in row
const int COLS = 8; // Number of pixels in column
const int BRIGHTNESS = 40; // Brightness of NeoPixel

// These globals store the data from the API
int currentDir = -1;   // ⭐ start as invalid
double currentPeriod = 0;
double currentHeight = 0;

unsigned long lastUpdate = 0;
const unsigned long updateInterval = 60 * 1000; // refresh every 1 min

// MATRIX DECLARATION:
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(ROWS, COLS, PIN,
  NEO_MATRIX_TOP   + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG, // (0,0) is TOP-RIGHT
  NEO_GRB          + NEO_KHZ800);

// ---------- Location (Near Golden Gate Bridge) ----------
const double latitude  = 37.8199;
const double longitude = -122.4783;

// ---------- Open-Meteo API ----------
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
  int pos;       // x or y coordinate of the line
  uint16_t color;  // Color of this ripple
  bool active = false; // Is this ripple currently on-screen?
  int direction; // Stores the snapped visual direction (0, 90, 180, 270)
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
 * @brief Fetches the wave data from the OpenMeteo API
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
        currentDir = -1;   // ⭐ invalidate reading
        http.end();
        return;
      }

      // Read all values from the JSON
      currentDir = double(jsonObject["current"]["wave_direction"]);
      currentPeriod = double(jsonObject["current"]["wave_period"]);
      currentHeight = double(jsonObject["current"]["wave_height"]); 

      Serial.print("API Direction: ");
      Serial.print(currentDir);
      Serial.println("°");
      Serial.print("Period: ");
      Serial.print(currentPeriod);
      Serial.println(" seconds");
      Serial.print("Height: ");
      Serial.println(currentHeight);
    } else {
      Serial.print("HTTP error: ");
      Serial.println(httpResponseCode);
      currentDir = -1;   // ⭐ invalidate reading
    }
    http.end();
  } else {
    Serial.println("WiFi disconnected. Reconnecting...");
    WiFi.reconnect();
    currentDir = -1;   // ⭐ invalidate reading
  }
}

/**
 * @brief Snaps a raw angle (0-360) from the API to the correct
 * visual case for our drawing logic.
 * API: 0=N, 90=E, 180=S, 270=W
 * Visual Cases: 90=N, 0=E, 270=S, 180=W
 */
int snapDirection(int dir) {
  // This logic maps API direction to the correct visual case.
  if (dir > 45 && dir <= 135) { // API is EAST (90)
    return 0; // Return visual EAST (case 0)
  } else if (dir > 135 && dir <= 225) { // API is SOUTH (180)
    return 270; // Return visual SOUTH (case 270)
  } else if (dir > 225 && dir <= 315) { // API is WEST (270)
    return 180; // Return visual WEST (case 180)
  } else { // API is NORTH (0 or 315-45)
    return 90; // Return visual NORTH (case 90)
  }
}


/**
 * @brief This is the function you requested.
 * It's called continuously from the main loop.
 * It manages spawning, updating, and drawing all ripples.
 */
void visualizeRipple(int dir, double period, double height) {
  int snappedDir = snapDirection(dir);

  period /= 5; // make period 5 times as fast

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
  updateRipples(); // No longer needs direction

  // 3. Draw all ripples to the buffer
  uint16_t dimBlueBg = matrix.Color(20, 20, 40); 
  matrix.fillScreen(dimBlueBg); 
  drawRipples(); // Draw ripples on top

  // 4. Show the new frame
  matrix.show();
}

/**
 * @brief Finds an inactive ripple in the array and spawns it at the correct edge.
 * @param snappedDir The visual direction (0, 90, 180, 270)
 * @param height The wave height (used for color)
 */
void addNewRipple(int snappedDir, double height) {
  for (int i = 0; i < MAX_RIPPLES; i++) {
    if (!ripples[i].active) { // Found a free slot
      ripples[i].active = true;
      ripples[i].direction = snappedDir; // Store the direction

      // 1. Set start position based on direction
      // 'pos' is the line's coordinate.
      int w = matrix.width();
      int h = matrix.height();
      switch (snappedDir) { 
        case 0:   // Visual East (starts from right, moves right)
          ripples[i].pos = (w - 1); // x = 7
          break;
        case 180: // Visual West (starts from left, moves left)
          ripples[i].pos = 0; // x = 0
          break;
        case 90:  // Visual North (starts from bottom, moves up)
          ripples[i].pos = (h - 1); // y = 7
          break;
        case 270: // Visual South (starts from top, moves down)
          ripples[i].pos = 0; // y = 0
          break;
      }

      // 2. Set color based on height
      int blue = (int)(constrain(height, 0.0, 2.0) / 2.0 * 255);
      ripples[i].color = matrix.Color(0, 0, blue);

      if (height > 0 && blue == 0) {
        blue = 10; // A very dim blue
        ripples[i].color = matrix.Color(0, 0, blue);
      }
      
      return; // Exit after spawning one ripple
    }
  }
}

/**
 * @brief Updates the position of all active ripples.
 */
void updateRipples() {
  for (int i = 0; i < MAX_RIPPLES; i++) {
    if (ripples[i].active) {
      bool deactivating = false;
      int moveDir = ripples[i].direction;
      int w = matrix.width();
      int h = matrix.height();
      
      // 1. Move the ripple
      // (0,0) is top-right. X+ is LEFT. Y+ is DOWN.
      switch (moveDir) { 
        case 0:   // Visual East (moving right)
          ripples[i].pos--; // x moves right
          // Deactivate when line is off-screen
          if (ripples[i].pos < 0) deactivating = true;
          break;
        case 180: // Visual West (moving left)
          ripples[i].pos++; // x moves left
          // Deactivate when line is off-screen
          if (ripples[i].pos > (w - 1)) deactivating = true;
          break;
        case 90:  // Visual North (moving up)
          ripples[i].pos--; // y moves up
          if (ripples[i].pos < 0) deactivating = true;
          break;
        case 270: // Visual South (moving down)
          ripples[i].pos++; // y moves down
          if (ripples[i].pos > (h - 1)) deactivating = true;
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
 * @brief Draws all active ripples to the matrix buffer with slight variations.
 */
void drawRipples() {
  for (int i = 0; i < MAX_RIPPLES; i++) {
    if (ripples[i].active) {
      int drawDir = ripples[i].direction;
      uint16_t color = ripples[i].color;
      int mainPos = ripples[i].pos; // The main coordinate for the line
      int maxCoord = max(ROWS, COLS) - 1; // Max index (7 for 8x8 matrix)

      // <<< FIX: Loop through perpendicular axis and add wobble to main axis >>>
      switch (drawDir) {
        case 90:  // North (moving up, horizontal line)
        case 270: // South (moving down, horizontal line)
          // `mainPos` is the Y-coordinate. We vary the X-coordinate for each pixel.
          for (int x = 0; x <= maxCoord; x++) {
            int wobble = random(0, 2); // 0 or 1
            int variedY = constrain(mainPos + wobble, 0, maxCoord);
            matrix.drawPixel(x, variedY, color);
          }
          break;
        case 0:   // East (moving right, vertical line)
        case 180: // West (moving left, vertical line)
          // `mainPos` is the X-coordinate. We vary the Y-coordinate for each pixel.
          for (int y = 0; y <= maxCoord; y++) {
            int wobble = random(0, 2); // 0 or 1
            int variedX = constrain(mainPos + wobble, 0, maxCoord);
            matrix.drawPixel(variedX, y, color);
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
  getWaveData();   // initial fetch

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
  delay(100); // ~1.1 frames per second
}


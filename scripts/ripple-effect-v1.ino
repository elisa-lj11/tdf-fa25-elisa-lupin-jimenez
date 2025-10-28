/*
Ripple-effect-v1
Getting the right movement with the wave ripple to visualize wave API data
Vibe-coded with Gemini: https://gemini.google.com/share/952c75304788
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
  NEO_MATRIX_TOP    + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG, // *** FIX: Match zig-zag wiring ***
  NEO_GRB           + NEO_KHZ800);

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
  int direction; // *** FIX: Add direction to the ripple itself ***
};

#define MAX_RIPPLES 5 // Max simultaneous ripples we can track
Ripple ripples[MAX_RIPPLES]; // The array to hold all our ripples

unsigned long lastRippleTime = 0; // When the last ripple was spawned
unsigned long currentPeriodInMillis = 3000; // Stores the period
// --- Removed confusing global 'currentDirection' ---

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

      Serial.print("Direction: ");
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
 * @brief Snaps a raw angle (0-360) to the closest 90-degree axis.
 * 0 = East, 90 = North, 180 = West, 270 = South
 */
int snapDirection(int dir) {
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
  // *** FIX: Snap the direction *once* per frame ***
  int snappedDir = snapDirection(dir);

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
  updateRipples(); // *** FIX: No longer needs direction ***

  // 3. Draw all ripples to the buffer
  // *** MODIFICATION: Set dim blue background as requested ***
  uint16_t dimBlueBg = matrix.Color(20, 20, 40); // Define dim blue background
  matrix.fillScreen(dimBlueBg); // Set dim blue background
  drawRipples(); // Draw ripples on top

  // 4. Show the new frame
  matrix.show();
}

/**
 * @brief Finds an inactive ripple in the array and spawns it at the correct edge.
 * @param snappedDir The direction (0, 90, 180, 270)
 * @param height The wave height (used for color)
 */
void addNewRipple(int snappedDir, double height) {
  for (int i = 0; i < MAX_RIPPLES; i++) {
    if (!ripples[i].active) { // Found a free slot
      ripples[i].active = true;
      ripples[i].direction = snappedDir; // *** FIX: Store the direction ***

      // 1. Set start position based on direction
      // 'pos' is now the peak of the arc.
      // The arc is 4 pixels deep (pos to pos+3), so we start it 3 pixels off-screen
      int w = matrix.width();
      int h = matrix.height();
      switch (snappedDir) { // Use snappedDir
        case 0:   // East (starts from left)
          ripples[i].pos = (w - 1) + 3; // x = 10 
          break;
        case 180: // Visual West (starts from left, moves left)
          ripples[i].pos = -3; // x = -3
          break;
        case 90:  // North (starts from bottom)
          ripples[i].pos = (h - 1) + 3; // y = 10
          break;
        case 270: // South (starts from top)
          ripples[i].pos = -3; // y = -3
          break;
      }

      // 2. Set color based on height
      // Map height (e.g., 0.0 - 2.0 meters) to a blue value
      // Let's assume a max expected height of 2.0m for 100% brightness
      int blue = (int)(constrain(height, 0.0, 2.0) / 2.0 * 255);
      ripples[i].color = matrix.Color(0, 0, blue);

      // Ensure a minimum brightness if height is very small but not zero
      if (height > 0 && blue == 0) {
        blue = 10; // A very dim blue
        ripples[i].color = matrix.Color(0, 0, blue);
      }
      
      return; // Exit after spawning one ripple
    }
  }
  // If we get here, the ripple array is full
}

/**
 * @brief Updates the position of all active ripples.
 */
void updateRipples() {
  for (int i = 0; i < MAX_RIPPLES; i++) {
    if (ripples[i].active) {
      bool deactivating = false;
      int moveDir = ripples[i].direction; // *** FIX: Use ripple's own direction ***
      int w = matrix.width();
      int h = matrix.height();
      
      // 1. Move the ripple
      // 'pos' is the peak of the arc. The arc is 4 pixels deep.
      switch (moveDir) { // Use moveDir
        case 0:   // East (moving right)
          ripples[i].pos--; // x moves right
          if (ripples[i].pos < 0) deactivating = true; // Deactivate when peak hits far edge
          break;
        case 180: // West (moving left)
          ripples[i].pos++; // x moves left
          if (ripples[i].pos > (w - 1)) deactivating = true; // Deactivate when peak hits far edge
          break;
        case 90:  // North (moving up)
          ripples[i].pos--; // y moves up
          if (ripples[i].pos < 0) deactivating = true;
          break;
        case 270: // South (moving down)
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
 * @brief Draws all active ripples to the matrix buffer.
 */
void drawRipples() {
  // *** FIX: Use 7-segment drawLine() to create a symmetrical arc ***
  // *** FIX: Swapped arc directions to match user request ***
  
  for (int i = 0; i < MAX_RIPPLES; i++) {
    if (ripples[i].active) {
      int drawDir = ripples[i].direction;
      uint16_t color = ripples[i].color;
      int x, y;

      switch (drawDir) {
        case 90:  // North (moving up, arc now opens up)
          y = ripples[i].pos;
          matrix.drawLine(3, y,   4, y,   color); // Center
          matrix.drawLine(2, y-1, 3, y,   color); // Left inner
          matrix.drawLine(4, y,   5, y-1, color); // Right inner
          matrix.drawLine(1, y-2, 2, y-1, color); // Left middle
          matrix.drawLine(5, y-1, 6, y-2, color); // Right middle
          matrix.drawLine(0, y-3, 1, y-2, color); // Left outer
          matrix.drawLine(6, y-2, 7, y-3, color); // Right outer
          break;
        case 270: // South (moving down, arc now opens down)
          y = ripples[i].pos;
          matrix.drawLine(3, y,   4, y,   color); // Center
          matrix.drawLine(2, y+1, 3, y,   color); // Left inner
          matrix.drawLine(4, y,   5, y+1, color); // Right inner
          matrix.drawLine(1, y+2, 2, y+1, color); // Left middle
          matrix.drawLine(5, y+1, 6, y+2, color); // Right middle
          matrix.drawLine(0, y+3, 1, y+2, color); // Left outer
          matrix.drawLine(6, y+2, 7, y+3, color); // Right outer
          break;
        case 0:   // East (moving right, arc now opens right)
          x = ripples[i].pos;
          matrix.drawLine(x,   3, x,   4, color); // Center
          matrix.drawLine(x+1, 2, x,   3, color); // Top inner
          matrix.drawLine(x,   4, x+1, 5, color); // Bottom inner
          matrix.drawLine(x+2, 1, x+1, 2, color); // Top middle
          matrix.drawLine(x+1, 5, x+2, 6, color); // Bottom middle
          matrix.drawLine(x+3, 0, x+2, 1, color); // Top outer
          matrix.drawLine(x+2, 6, x+3, 7, color); // Bottom outer
          break;
        case 180: // West (moving left, arc now opens left)
          x = ripples[i].pos;
          matrix.drawLine(x,   3, x,   4, color); // Center
          matrix.drawLine(x-1, 2, x,   3, color); // Top inner
          matrix.drawLine(x,   4, x-1, 5, color); // Bottom inner
          matrix.drawLine(x-2, 1, x-1, 2, color); // Top middle
          matrix.drawLine(x-1, 5, x-2, 6, color); // Bottom middle
          matrix.drawLine(x-3, 0, x-2, 1, color); // Top outer
          matrix.drawLine(x-2, 6, x-3, 7, color); // Bottom outer
          break;
      }
    }
  }
}

// ---------- Setup ----------
void setup() {
  // *** FIX: Move Serial.begin() to the top ***
  Serial.begin(9600);
  while (!Serial); // Wait for Serial to be ready (for some boards)
  delay(100); 
  Serial.println("Serial connection established.");

  matrix.begin();
  matrix.setBrightness(BRIGHTNESS);
  matrix.show(); // Initialize matrix to off
  Serial.println("Matrix initialized.");

  // === HARDWARE TEST ===
  Serial.println("Starting hardware test...");
  // Draw a single RED pixel at (0, 0)
  matrix.drawPixel(0, 0, matrix.Color(255, 0, 0)); 
  matrix.show(); // Show the pixel
  Serial.println("Hardware test: Red pixel at (0,0) should be on for 2 sec.");
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
  // 100ms = ~10 frames per second
  delay(300);
}


/*
This version uses mpu6050_calibration2.ino for calibration offset values that are
preserved in memory. It tracks and outputs the sensor's orientation in 8 discrete
states (plus a Neutral/Flat state) based on Pitch and Roll.

Help from Gemini: https://gemini.google.com/share/dc475f42581a
*/

#include <Wire.h>
#include <Haptic_Driver.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <secrets.h>

// --- I2C/Power Definitions ---
#define I2C_SDA_PIN 22
#define I2C_SCL_PIN 20
#define I2C_POWER_PIN 2 // Specific to Feather ESP32 V2

// --- Driver Objects ---
Haptic_Driver hapDrive;
Adafruit_MPU6050 mpu;

// --- WiFi Object ---
WiFiUDP Udp;
const bool SHOULD_USE_WIFI = true; // Set this to false for debugging

// --- WiFi credentials (Assumes a secrets.h file exists) ---
// NOTE: Make sure you have a secrets.h file with SECRET_SSID, SECRET_PASSWORD, and SECRET_LAPTOP_IP defined.
const char* SSID = SECRET_SSID;
const char* PASSWORD = SECRET_PASSWORD;
const char* TD_IP = SECRET_LAPTOP_IP; // The IP of your TouchDesigner computer
const int TD_PORT = 4210;  // Must match the Port in TouchDesigner's UDP In DAT

// --- Haptic Settings ---
const float MAX_VIBRATION_INTENSITY = 127.0;

// --- Motion Detection Settings ---
const float MOTION_THRESHOLD = 2.0; 
const float MAX_MOVEMENT_MAGNITUDE = 15.0; 
const float GYRO_SCALING_FACTOR = 1.0; // Adjust how much rotation contributes to vibration

// --- Orientation Tracking Settings ---
// The normalized threshold (0.0 to 1.0) to determine if a tilt is "significant" enough.
// 0.4 corresponds roughly to 36 degrees of tilt (0.4 * 90 degrees).
const float ORIENTATION_THRESHOLD_NORM = 0.4;

// --- Baseline Tracking for Orientation-Independent Motion (Accelerometer) ---
float baselineMagnitude = 0.0;
const float BASELINE_SMOOTHING_FACTOR = 0.05; 

// --- Calibration Values based off mpu6050_calibration2.ino (Accelerometer)
float accelOffsetX = 1.1262;
float accelOffsetY = -0.0034;
float accelOffsetZ = -0.6791;
float gyroOffsetX = -0.0153;
float gyroOffsetY = -0.0056;
float gyroOffsetZ = 0.0016;

// --- Timer Definitions for Inverse Logic ---
unsigned long lastMovementTime = 0;

// How long the device must be still (in milliseconds) before the vibration stops.
const unsigned long STILLNESS_TIMEOUT_MS = 200;

// --- Function Prototypes ---
void setupWiFi();
void setupHapticDriver();
void setupMPU6050();
float calculateVectorMagnitude(float x, float y, float z);
int getOrientationState(float pitchNorm, float rollNorm);


// ------------------------------------
// Setup
// ------------------------------------
void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("Enabling I2C/STEMMA QT Power (HIGH on GPIO 2).");
    pinMode(I2C_POWER_PIN, OUTPUT);
    digitalWrite(I2C_POWER_PIN, HIGH);
    delay(100);

    // Initialize I2C with specified SDA/SCL pins
    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);

    if (SHOULD_USE_WIFI) {
        setupWiFi();
        // Bind the UDP port to allow sending
        Udp.begin(WiFi.localIP(), TD_PORT);
    }

    setupHapticDriver();
    setupMPU6050();

    Serial.println("Initialization complete. Ready for inverse-logic proportional motion detection.");
    Serial.println("");
    delay(1000);
}

// ------------------------------------
// Wifi Setup
// ------------------------------------
void setupWiFi() {
    Serial.println("Connecting to WiFi...");
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("WiFi connected!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

// ------------------------------------
// Haptic Driver Setup
// ------------------------------------
void setupHapticDriver() {
    Serial.println("--- Haptic Driver Setup ---");
    if (!hapDrive.begin()) {
        Serial.println("Could not communicate with Haptic Driver.");
    } else {
        Serial.println("Qwiic Haptic Driver DA7280 found!");
    }
    if (!hapDrive.defaultMotor()) {
        Serial.println("Could not set default settings.");
    }
    hapDrive.enableFreqTrack(false);
    hapDrive.setOperationMode(DRO_MODE); // Direct Register Operation Mode
    Serial.println("Haptic Driver Ready.");
}

// ------------------------------------
// MPU6050 Setup
// ------------------------------------
void setupMPU6050() {
    Serial.println("--- MPU6050 Setup ---");
    // Try to begin MPU. The default address is 0x68.
    if (!mpu.begin()) {
        Serial.println("Failed to find MPU6050 chip. Check I2C wiring (SDA/SCL on 22/20) and power.");
        while (1) {
            delay(10);
        }
    }
    Serial.println("MPU6050 Found!");
    mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
    mpu.setGyroRange(MPU6050_RANGE_250_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
    Serial.println("MPU6050 Ready for Polling.");
}

// ------------------------------------
// Vector Magnitude Calculation
// ------------------------------------
float calculateVectorMagnitude(float x, float y, float z) {
    return sqrt(x * x + y * y + z * z);
}

// ------------------------------------
// Orientation State Calculation
// Maps Pitch and Roll to one of 8 states (1-8) or Neutral (0)
// ------------------------------------
int getOrientationState(float pitchNorm, float rollNorm) {
    // P: Normalized Pitch (-1.0 to 1.0) | R: Normalized Roll (-1.0 to 1.0)
    float P = pitchNorm;
    float R = rollNorm;

    // Using a constant threshold to define "significant" tilt
    const float TH = ORIENTATION_THRESHOLD_NORM;

    // State 1: Flat/Neutral (low tilt on both axes)
    if (abs(P) < TH && abs(R) < TH) {
        return 1;
    }

    // State 2: Front (High Pitch, Low Roll)
    if (P >= TH && abs(R) < TH) {
        return 2;
    }
    
    // State 3: Back (Low Pitch, Low Roll)
    if (P <= -TH && abs(R) < TH) {
        return 3;
    }

    // State 4: Right (Low Pitch, High Roll)
    if (R >= TH && abs(P) < TH) {
        return 4;
    }

    // State 5: Left (Low Pitch, Low Roll)
    if (R <= -TH && abs(P) < TH) {
        return 5;
    }

    // State 6: Front-Right Corner (High Tilt on both positive axes)
    if (P >= TH && R >= TH) {
        return 6;
    }
    
    // State 7: Front-Left Corner (High Tilt on positive Pitch, negative Roll)
    if (P >= TH && R <= -TH) {
        return 7;
    }

    // State 8: Back Corner (Covers both Back-Right and Back-Left)
    // This ensures we get exactly 8 states by combining the less-used back corner states.
    if (P <= -TH && abs(R) >= TH) {
        return 8;
    }
    
    // Fallback (should be covered by the logic above, but ensures a value is returned)
    return 1; 
}


// ------------------------------------
// Main Loop (Polling and Inverse Proportional Control)
// ------------------------------------
void loop() {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // ... (Motion Tracking Logic remains the same) ...
    
    float currentAccMagnitude = calculateVectorMagnitude(a.acceleration.x, a.acceleration.y, a.acceleration.z);
    float currentGyroMagnitude = calculateVectorMagnitude(g.gyro.x, g.gyro.y, g.gyro.z);
    
    // --- 1. Update the Baseline ---
    if (baselineMagnitude == 0.0) {
        baselineMagnitude = currentAccMagnitude;
    } else {
        baselineMagnitude = (currentAccMagnitude * BASELINE_SMOOTHING_FACTOR) + 
                            (baselineMagnitude * (1.0 - BASELINE_SMOOTHING_FACTOR));
    }
    
    // --- 2. Calculate Total Motion Magnitude ---
    float accDeviation = abs(currentAccMagnitude - baselineMagnitude);
    float rotationContribution = currentGyroMagnitude * GYRO_SCALING_FACTOR;
    float totalMotionMagnitude = accDeviation + rotationContribution;
    
    uint8_t vibrateIntensity = 0;
    bool isMoving = (totalMotionMagnitude > MOTION_THRESHOLD);

    // --- ORIENTATION & INVERTED VIBRATION LOGIC ---
    
    // Apply calibration for orientation calculation, even if not moving
    float accelX = a.acceleration.x - accelOffsetX;
    float accelY = a.acceleration.y - accelOffsetY;
    float accelZ = a.acceleration.z - accelOffsetZ;
    
    // Calculate pitch and roll from accelerometer (in radians)
    float pitchRad = atan2(accelY, sqrt(accelX * accelX + accelZ * accelZ));
    float rollRad = atan2(-accelX, accelZ);
    
    // Convert to degrees (for internal print, not strictly needed for pitch/rollNorm)
    float pitchDeg = pitchRad * 180.0 / PI;
    float rollDeg = rollRad * 180.0 / PI;
    
    // Normalize to -1.0 to +1.0 range (Pitch: +/-90, Roll: +/-180)
    float pitchNorm = constrain(pitchDeg / 90.0, -1.0, 1.0);
    float rollNorm = constrain(rollDeg / 180.0, -1.0, 1.0);

    // --- NEW: Get the 8-State Orientation ID ---
    int orientationState = getOrientationState(pitchNorm, rollNorm);

    if (isMoving) {
        // Movement detected: Calculate proportional intensity and reset timer
        lastMovementTime = millis();

        // --- PROPORTIONAL MAPPING ---
        float constrainedDeviation = constrain(totalMotionMagnitude, MOTION_THRESHOLD, MAX_MOVEMENT_MAGNITUDE);
        float mappedIntensity = 
            (constrainedDeviation - MOTION_THRESHOLD) * (MAX_VIBRATION_INTENSITY / (MAX_MOVEMENT_MAGNITUDE - MOTION_THRESHOLD));

        // Ensure intensity is at least 1 (to keep it running) and at most 127.
        vibrateIntensity = (uint8_t)constrain(mappedIntensity, 1.0, MAX_VIBRATION_INTENSITY);

        // --- UDP Sending ---
        if (vibrateIntensity > 0) {
            String dataString = "";

            // 1. Normalized Acceleration (X, Y, Z)
            dataString += String(accelX, 2) + ","; 
            dataString += String(accelY, 2) + ",";
            dataString += String(accelZ, 2) + ",";

            // 2. Normalized Pitch and Roll
            dataString += (String(pitchNorm, 4) + ",");
            dataString += (String(rollNorm, 4) + ",");

            // 3. NEW: Orientation State ID (Integer 1-8)
            dataString += String(orientationState) + ",";

            // 4. Final Vibrate Intensity
            dataString += String(vibrateIntensity); 
            
            if (SHOULD_USE_WIFI) {
                Udp.beginPacket(TD_IP, TD_PORT);
                Udp.write((const uint8_t*)dataString.c_str(), dataString.length());
                Udp.endPacket();
            }

            Serial.print("Sending: ");
            Serial.println(dataString);
        }
        
    } else {
        // No movement detected: Check the stillness timer
        if ((millis() - lastMovementTime) > STILLNESS_TIMEOUT_MS) {
            // Stop the motor if stillness timeout has elapsed.
            vibrateIntensity = 0; 
        } else {
            // Keep the motor running at a minimum level while waiting for timeout.
            vibrateIntensity = 1; 
        }
        
        // If not moving but not timed out, send the Flat state
        if (vibrateIntensity > 0) {
            String dataString = String(accelX, 2) + "," + String(accelY, 2) + "," + String(accelZ, 2) + ",";
            dataString += (String(pitchNorm, 4) + ",");
            dataString += (String(rollNorm, 4) + ",");
            dataString += String(orientationState) + ","; // Send the flat/current state
            dataString += String(vibrateIntensity);

            if (SHOULD_USE_WIFI) {
                Udp.beginPacket(TD_IP, TD_PORT);
                Udp.write((const uint8_t*)dataString.c_str(), dataString.length());
                Udp.endPacket();
            }
        }
    }

    // Set the calculated intensity (0 or 1 to 127) every loop iteration.
    hapDrive.setVibrate(vibrateIntensity);

    // Reduced delay for smoother haptics
    delay(10); 
}
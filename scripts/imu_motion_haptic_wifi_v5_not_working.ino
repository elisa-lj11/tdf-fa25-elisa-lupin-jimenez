/*
Modified code: Focuses on 2D Translational Position (posX, posY) based on 
double-integration of calibrated and gravity-compensated accelerometer data.
This tracks side-to-side (X) and up-down (Y) movement relative to the start position,
excluding forward/back (Z) movement.

**FIXED:** Added ACCEL_NOISE_THRESHOLD to aggressively zero out small acceleration
readings, which prevents perpetual drift in the position (posX, posY).

DOES NOT WORK, LOTS OF DRIFT STILL

Help from Gemini: https://gemini.google.com/share/a9c9bb723063
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
const int TD_PORT = 4210; // Must match the Port in TouchDesigner's UDP In DAT

// --- Haptic Settings ---
const float MAX_VIBRATION_INTENSITY = 127.0;

// --- Motion Detection Settings ---
const float MOTION_THRESHOLD = 2.0; 
const float MAX_MOVEMENT_MAGNITUDE = 15.0; 
const float GYRO_SCALING_FACTOR = 1.0; 

// --- Orientation Tracking Settings (Used for Gravity Compensation) ---
const float ORIENTATION_THRESHOLD_NORM = 0.4;

// --- Baseline Tracking for Orientation-Independent Motion (Accelerometer) ---
float baselineMagnitude = 0.0;
const float BASELINE_SMOOTHING_FACTOR = 0.05; 

// --- Calibration Values based off mpu6050_calibration2.ino ---
float accelOffsetX = 1.1262;
float accelOffsetY = -0.0034;
float accelOffsetZ = -0.6791;
float gyroOffsetX = -0.0153;
float gyroOffsetY = -0.0056;
float gyroOffsetZ = 0.0016;

// --- Timer Definitions for Inverse Logic ---
unsigned long lastMovementTime = 0;
const unsigned long STILLNESS_TIMEOUT_MS = 200;

// --- Translational Tracking Variables (NEW) ---
float velX = 0.0; // Translational Velocity X-axis (side-to-side)
float velY = 0.0; // Translational Velocity Y-axis (up-down)
float posX = 0.0; // Translational Position X-axis
float posY = 0.0; // Translational Position Y-axis

// Filter constants for stability
// High-pass filter/decay factor for velocity to counteract drift.
const float VELOCITY_DECAY = 0.995; // Slightly slower decay for a more responsive feel

// **CRITICAL FIX**: Threshold to zero out acceleration noise (m/s^2)
// Any movement under this magnitude is considered sensor noise and will not be integrated.
const float ACCEL_NOISE_THRESHOLD = 0.5; 
// Minimum velocity magnitude (m/s) required to update position
const float VELOCITY_INTEGRATION_THRESHOLD = 0.05; 
// Time tracking for integration
unsigned long previousTime = 0;

// --- Function Prototypes ---
void setupWiFi();
void setupHapticDriver();
void setupMPU6050();
float calculateVectorMagnitude(float x, float y, float z);
int getOrientationState(float pitchNorm, float rollNorm);
void resetPosition();

// ------------------------------------
// Position Reset Utility
// ------------------------------------
void resetPosition() {
    posX = 0.0;
    posY = 0.0;
    velX = 0.0;
    velY = 0.0;
    Serial.println("Position and Velocity Reset.");
}


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
    
    // Initialize previousTime for the first delta-t calculation
    previousTime = millis(); 

    Serial.println("Initialization complete. Ready for 2D translational tracking.");
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
// ------------------------------------
int getOrientationState(float pitchNorm, float rollNorm) {
    float P = pitchNorm;
    float R = rollNorm;
    const float TH = ORIENTATION_THRESHOLD_NORM;
    if (abs(P) < TH && abs(R) < TH) { return 1; }
    if (P >= TH && abs(R) < TH) { return 2; }
    if (P <= -TH && abs(R) < TH) { return 3; }
    if (R >= TH && abs(P) < TH) { return 4; }
    if (R <= -TH && abs(P) < TH) { return 5; }
    if (P >= TH && R >= TH) { return 6; }
    if (P >= TH && R <= -TH) { return 7; }
    if (P <= -TH && abs(R) >= TH) { return 8; }
    return 1; 
}


// ------------------------------------
// Main Loop (2D Translational Tracking)
// ------------------------------------
void loop() {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // Calculate time step (Delta Time) in seconds
    unsigned long currentTime = millis();
    float dt = (currentTime - previousTime) / 1000.0; // Convert to seconds
    previousTime = currentTime;

    // --- 1. Calibrated Accelerometer Readings ---
    float accelX_cal = a.acceleration.x - accelOffsetX;
    float accelY_cal = a.acceleration.y - accelOffsetY;
    float accelZ_cal = a.acceleration.z - accelOffsetZ;
    
    // Calculate pitch and roll (in radians) to determine orientation
    float pitchRad = atan2(accelY_cal, sqrt(accelX_cal * accelX_cal + accelZ_cal * accelZ_cal));
    float rollRad = atan2(-accelX_cal, accelZ_cal);
    
    // --- 2. GRAVITY COMPENSATION (Translational Acceleration) ---
    const float G_FORCE = 9.81; 

    // Gravity vector component along the sensor's X and Y axes
    float gravityX = G_FORCE * sin(rollRad);
    float gravityY = G_FORCE * sin(pitchRad);
    
    // The net translational acceleration (acceleration due to user movement)
    float accel_transX = accelX_cal - gravityX; 
    float accel_transY = accelY_cal - gravityY; 

    // --- 3. CRITICAL: ACCELERATION NOISE THRESHOLD ---
    // If translational acceleration is small (i.e., noise or minor drift), zero it out.
    if (abs(accel_transX) < ACCEL_NOISE_THRESHOLD) {
        accel_transX = 0.0;
    }
    if (abs(accel_transY) < ACCEL_NOISE_THRESHOLD) {
        accel_transY = 0.0;
    }
    
    // --- 4. Integration (Velocity and Position Update) ---
    
    // Integrate translational acceleration to get velocity
    velX += accel_transX * dt;
    velY += accel_transY * dt;

    // Apply High-Pass Filter (Decay) to counteract long-term drift in velocity
    velX *= VELOCITY_DECAY;
    velY *= VELOCITY_DECAY;

    Serial.println("velX: " + String(velX, 4) + " , velY: " + String(velY, 4));

    // Only integrate position if there is significant velocity detected
    if (abs(velX) > VELOCITY_INTEGRATION_THRESHOLD || abs(velY) > VELOCITY_INTEGRATION_THRESHOLD) {
      // Integrate velocity to get position
      posX += velX * dt;
      posY += velY * dt;
    } else {
      // If velocity is near zero, slowly decay the position back toward zero to fix minor remaining drift
      posX *= 0.999;
      posY *= 0.999;
    }

    // --- 5. HAPTICS/VIBRATION LOGIC (Retained from original code) ---
    float currentAccMagnitude = calculateVectorMagnitude(a.acceleration.x, a.acceleration.y, a.acceleration.z);
    float currentGyroMagnitude = calculateVectorMagnitude(g.gyro.x, g.gyro.y, g.gyro.z);
    
    if (baselineMagnitude == 0.0) {
        baselineMagnitude = currentAccMagnitude;
    } else {
        baselineMagnitude = (currentAccMagnitude * BASELINE_SMOOTHING_FACTOR) + 
                             (baselineMagnitude * (1.0 - BASELINE_SMOOTHING_FACTOR));
    }
    
    float accDeviation = abs(currentAccMagnitude - baselineMagnitude);
    float rotationContribution = currentGyroMagnitude * GYRO_SCALING_FACTOR;
    float totalMotionMagnitude = accDeviation + rotationContribution;
    
    uint8_t vibrateIntensity = 0;
    bool isMoving = (totalMotionMagnitude > MOTION_THRESHOLD);

    // --- HAPTICS & UDP SENDING LOGIC ---
    float pitchDeg = pitchRad * 180.0 / PI;
    float rollDeg = rollRad * 180.0 / PI;
    float pitchNorm = constrain(pitchDeg / 90.0, -1.0, 1.0);
    float rollNorm = constrain(rollDeg / 180.0, -1.0, 1.0);
    int orientationState = getOrientationState(pitchNorm, rollNorm);


    if (isMoving) {
        lastMovementTime = millis();
        // Calculate proportional intensity
        float constrainedDeviation = constrain(totalMotionMagnitude, MOTION_THRESHOLD, MAX_MOVEMENT_MAGNITUDE);
        float mappedIntensity = 
            (constrainedDeviation - MOTION_THRESHOLD) * (MAX_VIBRATION_INTENSITY / (MAX_MOVEMENT_MAGNITUDE - MOTION_THRESHOLD));
        vibrateIntensity = (uint8_t)constrain(mappedIntensity, 1.0, MAX_VIBRATION_INTENSITY);

        // Check for long stillness after movement to auto-reset
        // if ((millis() - lastMovementTime) > 5000) { // 5 seconds of total stillness
        //     resetPosition();
        // }

        // --- UDP Sending: POS X, Y Output ---
        if (vibrateIntensity > 0) {
            // Updated data string format to include the new position values
            String dataString = String(accelX_cal, 2) + "," + String(accelY_cal, 2) + "," + String(accelZ_cal, 2) + ",";
            dataString += (String(pitchNorm, 4) + ",");
            dataString += (String(rollNorm, 4) + ",");
            dataString += String(orientationState) + ","; 

            // 1. **X-Position (Translational)**
            dataString += String(posX, 4) + ","; 
            // 2. **Y-Position (Translational)**
            dataString += String(posY, 4) + ",";

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
            vibrateIntensity = 0; 
        } else {
            vibrateIntensity = 1; 
        }
        
        // Send the current POSX/POSY even when still (if motor is running)
        if (vibrateIntensity > 0) {
            String dataString = String(accelX_cal, 2) + "," + String(accelY_cal, 2) + "," + String(accelZ_cal, 2) + ",";
            dataString += (String(pitchNorm, 4) + ",");
            dataString += (String(rollNorm, 4) + ",");
            dataString += String(orientationState) + ","; // Send the flat/current state

            // 1. **X-Position (Translational)**
            dataString += String(posX, 4) + ","; 
            // 2. **Y-Position (Translational)**
            dataString += String(posY, 4) + ",";

            dataString += String(vibrateIntensity);

            if (SHOULD_USE_WIFI) {
                Udp.beginPacket(TD_IP, TD_PORT);
                Udp.write((const uint8_t*)dataString.c_str(), dataString.length());
                Udp.endPacket();
            }
        }
    }

    // Set the calculated intensity
    hapDrive.setVibrate(vibrateIntensity);
    delay(10); 
}
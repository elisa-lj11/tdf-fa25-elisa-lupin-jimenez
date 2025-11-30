/*
This version sets up ESP32 wifi and connects to TouchDesigner via UDP
The haptic vibration is now always running (at a minimum) and stops 
only after a period of stillness (200ms timeout).
It detects both acceleration and rotation for motion.

Help from Gemini: https://gemini.google.com/share/d90b1d460ae7
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
const char* SSID = SECRET_SSID;
const char* PASSWORD = SECRET_PASSWORD;
const char* TD_IP = SECRET_LAPTOP_IP; // The IP of your TouchDesigner computer
const int TD_PORT = 4210;             // Must match the Port in TouchDesigner's UDP In DAT

// --- Haptic Settings ---
const float MAX_VIBRATION_INTENSITY = 127.0;

// --- Motion Detection Settings ---
const float MOTION_THRESHOLD = 2.0; 
const float MAX_MOVEMENT_MAGNITUDE = 15.0; 
const float GYRO_SCALING_FACTOR = 1.0; // Adjust how much rotation contributes to vibration

// --- Baseline Tracking for Orientation-Independent Motion (Accelerometer) ---
float baselineMagnitude = 0.0;
const float BASELINE_SMOOTHING_FACTOR = 0.05; 

// --- NEW Timer Definitions for Inverse Logic ---
unsigned long lastMovementTime = 0;

// How long the device must be still (in milliseconds) before the vibration stops.
const unsigned long STILLNESS_TIMEOUT_MS = 200; // 0.5 seconds

// FIXME: counter for debug test prints
// int counter = 0;

// --- Function Prototypes ---
void setupWiFi();
void setupHapticDriver();
void setupMPU6050();
float calculateVectorMagnitude(float x, float y, float z);

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

    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);

    if (SHOULD_USE_WIFI) {
        setupWiFi();
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
    if (!mpu.begin()) {
        Serial.println("Failed to find MPU6050 chip");
        while (1) {
            delay(10);
        }
    }
    Serial.println("MPU6050 Found!");
    mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
    Serial.println("MPU6050 Ready for Polling.");
}

// ------------------------------------
// Vector Magnitude Calculation
// ------------------------------------
float calculateVectorMagnitude(float x, float y, float z) {
    return sqrt(x * x + y * y + z * z);
}


// ------------------------------------
// Main Loop (Polling and Inverse Proportional Control)
// ------------------------------------
void loop() {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // Get the current acceleration values in g's
    float currentAccX = a.acceleration.x;
    float currentAccY = a.acceleration.y;
    float currentAccZ = a.acceleration.z;

    // Get the current gyroscope values in rad/s
    float currentGyroX = g.gyro.x; 
    float currentGyroY = g.gyro.y;
    float currentGyroZ = g.gyro.z;

    float currentAccMagnitude = calculateVectorMagnitude(currentAccX, currentAccY, currentAccZ);
    float currentGyroMagnitude = calculateVectorMagnitude(currentGyroX, currentGyroY, currentGyroZ);
    
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

    // // FIXME: debug test prints
    // counter++;
    // if (counter == 50) {
    //     String notMovingTestString = "";
    //     notMovingTestString += "Acc x: " + String(a.acceleration.x, 2) + ", Acc y: " + String(a.acceleration.y, 2) + ", Acc z: " + String(a.acceleration.z, 2);
    //     Serial.println(notMovingTestString);
    //     Serial.print("baselineMagnitude: ");
    //     Serial.println(String(baselineMagnitude, 3));
    //     Serial.print("accMagnitude: ");
    //     Serial.println(String(currentAccMagnitude, 3));
    //     Serial.print("accDeviation:");
    //     Serial.println(String(accDeviation, 3));
    //     Serial.print("rotationContribution:");
    //     Serial.println(String(rotationContribution, 3));

    //     counter = 0;
    // }
    
    uint8_t vibrateIntensity = 0;
    bool isMoving = (totalMotionMagnitude > MOTION_THRESHOLD);

    // --- INVERTED VIBRATION LOGIC ---
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

            // Add Raw Acceleration (X, Y, Z)
            dataString += String(a.acceleration.x, 2) + ","; 
            dataString += String(a.acceleration.y, 2) + ",";
            dataString += String(a.acceleration.z, 2) + ",";

            // Add Raw Gyroscope (X, Y, Z)
            dataString += String(g.gyro.x, 2) + ",";
            dataString += String(g.gyro.y, 2) + ",";
            dataString += String(g.gyro.z, 2) + ",";

            // Add the calculated components and final intensity
            // dataString += String(accDeviation, 3) + ",";
            // dataString += String(rotationContribution, 3) + ",";
            // dataString += String(totalMotionMagnitude, 3) + ",";
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
    }

    // Set the calculated intensity (0 or 1 to 127) every loop iteration.
    hapDrive.setVibrate(vibrateIntensity);

    // Reduced delay for smoother haptics
    delay(10); 
}
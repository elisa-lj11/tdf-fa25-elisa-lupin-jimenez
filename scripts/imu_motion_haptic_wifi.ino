/*
This version sets up ESP32 wifi and connects to TouchDesigner via UDP
Help from Gemini: https://gemini.google.com/share/be968218553a
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

// --- WiFi credentials ---
const char* SSID = SECRET_SSID;
const char* PASSWORD = SECRET_PASSWORD;
const char* TD_IP = SECRET_LAPTOP_IP; // The IP of your TouchDesigner computer
const int TD_PORT = 4210;             // Must match the Port in TouchDesigner's UDP In DAT

// --- Haptic Settings ---
// The DA7280 accepts values from 0 to 127 in DRO_MODE with acceleration ON (default).
const float MAX_VIBRATION_INTENSITY = 127.0;

// --- Motion Detection Settings ---
// Threshold: Minimum movement magnitude to start vibration.
const float MOTION_THRESHOLD = 0.5; // g's, adjust this value to your liking.
// Maximum: Magnitude at which vibration is maximum. Needs to be tuned experimentally.
const float MAX_MOVEMENT_MAGNITUDE = 2.0; // g's, adjust this value.

// --- Baseline Tracking for Orientation-Independent Motion ---
float baselineMagnitude = 0.0;
// Factor for the exponential moving average (EMA) filter. 
// A smaller value (e.g., 0.01) makes the baseline update slower and less sensitive to movement.
const float BASELINE_SMOOTHING_FACTOR = 0.05; 

// --- Function Prototypes ---
void setupWiFi();
void setupHapticDriver();
void setupMPU6050();
float calculateMotionMagnitude(float accX, float accY, float accZ);

// ------------------------------------
// Setup
// ------------------------------------
void setup() {
    Serial.begin(115200);
    delay(1000);

    // Manually enable I2C Power (Specific to Feather ESP32 V2)
    Serial.println("Enabling I2C/STEMMA QT Power (HIGH on GPIO 2).");
    pinMode(I2C_POWER_PIN, OUTPUT);
    digitalWrite(I2C_POWER_PIN, HIGH);
    delay(100);

    // Use the following format for ESP32:
    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);

    setupWiFi();
    // Start the UDP listener on the ESP32 (though we are just sending)
    Udp.begin(WiFi.localIP(), TD_PORT);

    setupHapticDriver();
    setupMPU6050();

    Serial.println("Initialization complete. Ready for proportional motion detection.");
    Serial.println("");
    delay(1000);
}

// ------------------------------------
// Wifi Setup
// ------------------------------------
void setupWiFi() {
    Serial.println("Connecting to WiFi...");

    // Start WiFi connection
    WiFi.begin(SSID, PASSWORD);

    // Wait until connected
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
// Motion Magnitude Calculation
// ------------------------------------
float calculateMotionMagnitude(float accX, float accY, float accZ) {
    // Uses the Pythagorean theorem in 3D: Magnitude = sqrt(x^2 + y^2 + z^2)
    return sqrt(accX * accX + accY * accY + accZ * accZ);
}


// ------------------------------------
// Main Loop (Polling and Proportional Control)
// ------------------------------------
void loop() {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // Get the current acceleration values in g's
    float currentAccX = a.acceleration.x / SENSORS_GRAVITY_STANDARD;
    float currentAccY = a.acceleration.y / SENSORS_GRAVITY_STANDARD;
    float currentAccZ = a.acceleration.z / SENSORS_GRAVITY_STANDARD;

    // Calculate the total magnitude of the current acceleration vector
    float currentMagnitude = calculateMotionMagnitude(currentAccX, currentAccY, currentAccZ);

    // --- 1. Update the Baseline (Exponential Moving Average Filter) ---
    if (baselineMagnitude == 0.0) {
        // Initialize the baseline on first run
        baselineMagnitude = currentMagnitude;
    } else {
        // Smoothly adjust the baseline. This tracks gravity/static orientation.
        baselineMagnitude = (currentMagnitude * BASELINE_SMOOTHING_FACTOR) + 
                            (baselineMagnitude * (1.0 - BASELINE_SMOOTHING_FACTOR));
    }
    
    // --- 2. Calculate Motion Deviation ---
    // The deviation is the difference between the current reading and the smooth baseline.
    // This isolates the motion (high-frequency) from the gravity (low-frequency).
    float motionDeviation = abs(currentMagnitude - baselineMagnitude);
    
    uint8_t vibrateIntensity = 0;

    if (motionDeviation > MOTION_THRESHOLD) {
        // --- PROPORTIONAL MAPPING ---

        // 1. Constrain the deviation between the minimum threshold and the maximum magnitude.
        float constrainedDeviation = constrain(motionDeviation, MOTION_THRESHOLD, MAX_MOVEMENT_MAGNITUDE);
        
        // 2. Map the constrained range to the haptic motor's intensity range (0 to 127).
        float mappedIntensity = 
            (constrainedDeviation - MOTION_THRESHOLD) * (MAX_VIBRATION_INTENSITY / (MAX_MOVEMENT_MAGNITUDE - MOTION_THRESHOLD));

        // 3. Ensure the mapped intensity doesn't exceed the max value.
        vibrateIntensity = (uint8_t)constrain(mappedIntensity, 0.0, MAX_VIBRATION_INTENSITY);

        /* Debug prints for acceleremoter, gyroscope, and haptic strength
        Serial.print("Baseline: ");
        Serial.print(baselineMagnitude, 3);
        Serial.print("g, Deviation: ");
        Serial.print(motionDeviation, 3);
        Serial.print("g -> Intensity: ");
        Serial.println(vibrateIntensity);
        Serial.print("AccelX: ");
        Serial.print(a.acceleration.x);
        Serial.print(", ");
        Serial.print("AccelY: ");
        Serial.print(a.acceleration.y);
        Serial.print(", ");
        Serial.print("AccelZ: ");
        Serial.print(a.acceleration.z);
        Serial.print(", ");
        Serial.print("GyroX: ");
        Serial.print(g.gyro.x);
        Serial.print(", ");
        Serial.print("GyroY: ");
        Serial.print(g.gyro.y);
        Serial.print(", ");
        Serial.print("GyroZ: ");
        Serial.print(g.gyro.z);
        Serial.println("");
        */

        // --- 3. Format the Data String (The Payload) ---
        // Choose the data you want to send. We'll send the raw Accel and Gyro data.
        // Separated by commas (CSV format) for easy parsing in TouchDesigner.
        String dataString = "";

        // Add Raw Acceleration (X, Y, Z)
        dataString += String(a.acceleration.x, 2) + ","; // 2 decimal places
        dataString += String(a.acceleration.y, 2) + ",";
        dataString += String(a.acceleration.z, 2) + ",";

        // Add Raw Gyroscope (X, Y, Z)
        dataString += String(g.gyro.x, 2) + ",";
        dataString += String(g.gyro.y, 2) + ",";
        dataString += String(g.gyro.z, 2) + ",";

        // Add the calculated Motion Deviation and Haptic Intensity
        dataString += String(motionDeviation, 3) + ",";
        dataString += String(vibrateIntensity); 
        
        // Example: "1.23,-0.50,9.80,5.1,-2.3,1.0,0.456,127"

        // --- 4. Send the UDP Packet ---
        
        // Begin the packet transmission to the laptop's IP and Port
        Udp.beginPacket(TD_IP, TD_PORT);
        
        // Write the data string as the packet payload
        Udp.write((const uint8_t*)dataString.c_str(), dataString.length());

        // Finalize and send the packet
        Udp.endPacket();

        // ⚡️ OPTIONAL: Print to Serial Monitor for debugging
        Serial.print("Sending: ");
        Serial.println(dataString);

    } else {
        // Stop the motor if motion is below the threshold
        vibrateIntensity = 0;
    }

    // Set the calculated intensity (0 to 127)
    hapDrive.setVibrate(vibrateIntensity);

    // Small delay for I2C stability and to control the loop speed
    delay(50);
}
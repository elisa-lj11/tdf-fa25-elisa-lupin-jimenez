/*
Revised Code: Fluid Motion Detection using Baseline Tracking for Proportional Haptic Feedback.
This version fixes issues with detecting motion along the axis aligned with gravity.
Help from Gemini: https://gemini.google.com/share/443b40a2455e
*/

#include <Wire.h>
#include <Haptic_Driver.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// --- I2C/Power Definitions ---
#define I2C_SDA_PIN 22
#define I2C_SCL_PIN 20
#define I2C_POWER_PIN 2 // Specific to Feather ESP32 V2

// --- Driver Objects ---
Haptic_Driver hapDrive;
Adafruit_MPU6050 mpu;

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

    setupHapticDriver();
    setupMPU6050();

    Serial.println("Initialization complete. Ready for proportional motion detection.");
    Serial.println("");
    delay(1000);
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

        Serial.print("Baseline: ");
        Serial.print(baselineMagnitude, 3);
        Serial.print("g, Deviation: ");
        Serial.print(motionDeviation, 3);
        Serial.print("g -> Intensity: ");
        Serial.println(vibrateIntensity);/* Print out the values */
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

    } else {
        // Stop the motor if motion is below the threshold
        vibrateIntensity = 0;
    }

    // Set the calculated intensity (0 to 127)
    hapDrive.setVibrate(vibrateIntensity);

    // Small delay for I2C stability and to control the loop speed
    delay(50);
}
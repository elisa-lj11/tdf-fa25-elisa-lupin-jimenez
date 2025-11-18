/*
Merged Code: Activate Haptic Driver (DA7280) when motion is detected by MPU6050.
I2C is initialized for Feather ESP32 V2 with SDA on GPIO 22 and SCL on GPIO 20.
Help from Gemini: https://gemini.google.com/share/34327ef22b0c
*/

#include <Wire.h>
#include <Haptic_Driver.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// --- I2C/Power Definitions ---
#define I2C_SDA_PIN 22
#define I2C_SCL_PIN 20

// Define the specific pin used for I2C/NEOPIXEL Power on the Feather ESP32 V2
#define I2C_POWER_PIN 2

// --- Driver Objects ---
Haptic_Driver hapDrive;
Adafruit_MPU6050 mpu;

// --- Haptic Settings ---
const uint8_t VIBRATE_INTENSITY = 25; // Max 127 with acceleration on (default)
const int VIBRATE_ON_MS = 100;
const int VIBRATE_OFF_MS = 50;

// --- Function Prototypes ---
void setupHapticDriver();
void setupMPU6050();

// ------------------------------------
// Setup
// ------------------------------------
void setup() {
    Serial.begin(115200);
    delay(1000); // Give serial time to initialize

    // Manually enable I2C Power (Specific to Feather ESP32 V2)
    Serial.println("Enabling I2C/STEMMA QT Power (HIGH on GPIO 2).");
    pinMode(I2C_POWER_PIN, OUTPUT);
    digitalWrite(I2C_POWER_PIN, HIGH);
    delay(100); // Give power time to stabilize

    // Use the following format for ESP32:
    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);

    setupHapticDriver();
    setupMPU6050();

    Serial.println("Initialization complete. Ready for motion detection.");
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

    // Disable frequency tracking to avoid operation stopping errors.
    hapDrive.enableFreqTrack(false);

    Serial.println("Setting I2C Operation.");
    hapDrive.setOperationMode(DRO_MODE); // Direct Register Operation Mode
    Serial.println("Haptic Driver Ready.");
}

// ------------------------------------
// MPU6050 Setup
// ------------------------------------
void setupMPU6050() {
    Serial.println("--- MPU6050 Setup ---");

    // Try to initialize!
    if (!mpu.begin()) {
        Serial.println("Failed to find MPU6050 chip");
        while (1) {
            delay(10); // Halt on error
        }
    }
    Serial.println("MPU6050 Found!");

    // Setup motion detection
    mpu.setHighPassFilter(MPU6050_HIGHPASS_0_63_HZ);
    mpu.setMotionDetectionThreshold(1); // Adjust sensitivity as needed
    mpu.setMotionDetectionDuration(20); // Duration to sustain the threshold
    mpu.setInterruptPinLatch(true); // Keep IRQ latched until cleared by reading/initializing
    mpu.setInterruptPinPolarity(true);
    mpu.setMotionInterrupt(true);

    Serial.println("MPU6050 Motion Interrupt Enabled.");
}

// ------------------------------------
// Main Loop
// ------------------------------------
void loop() {
    // Check if the MPU6050 detected motion
    if (mpu.getMotionInterruptStatus()) {
        Serial.println("!!! MOTION DETECTED !!!");

        // Activate the Haptic Driver
        hapDrive.setVibrate(VIBRATE_INTENSITY);
        delay(VIBRATE_ON_MS);

        // Stop the motor
        hapDrive.setVibrate(0);
        delay(VIBRATE_OFF_MS); // Wait a moment before checking for new motion

        // The MPU6050 interrupt is latched. We must read the sensor events
        // to clear the interrupt flag and allow new motion detection.
        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);

        /* Optional: Print out the values */
        Serial.print("Cleared IRQ. AccelX: ");
        Serial.print(a.acceleration.x);
        Serial.print(", GyroZ: ");
        Serial.println(g.gyro.z);
    }

    // Small delay to prevent hammering the I2C bus too hard
    delay(10);
}
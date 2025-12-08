#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <EEPROM.h>

// --- I2C/Power Definitions ---
#define I2C_SDA_PIN 22
#define I2C_SCL_PIN 20
#define I2C_POWER_PIN 2 // Specific to Feather ESP32 V2

Adafruit_MPU6050 mpu;

// Pin configuration
const int CALIBRATE_BUTTON_PIN = 38; // Change this to your button pin

// Calibration offsets
float accelOffsetX = 0, accelOffsetY = 0, accelOffsetZ = 0;
float gyroOffsetX = 0, gyroOffsetY = 0, gyroOffsetZ = 0;

// Calibration state
bool isCalibrating = false;
bool calibrationComplete = false;
int calibrationSamples = 0;
const int MAX_SAMPLES = 500;

// Running sums for calibration
float accelXSum = 0, accelYSum = 0, accelZSum = 0;
float gyroXSum = 0, gyroYSum = 0, gyroZSum = 0;

// Button debouncing
unsigned long lastButtonPress = 0;
const unsigned long debounceDelay = 300;

// EEPROM addresses
const int EEPROM_MAGIC_ADDR = 0;
const int EEPROM_DATA_ADDR = 4;
const uint32_t EEPROM_MAGIC = 0xCAFEBABE; // Magic number to verify valid data

struct CalibrationData {
  float accelOffsetX;
  float accelOffsetY;
  float accelOffsetZ;
  float gyroOffsetX;
  float gyroOffsetY;
  float gyroOffsetZ;
};

void setup() {
  Serial.begin(115200);
  delay(1000);
  //while (!Serial) delay(100);

  // ESP32 requires EEPROM.begin()
  EEPROM.begin(512);

  pinMode(CALIBRATE_BUTTON_PIN, INPUT);
  pinMode(I2C_POWER_PIN, OUTPUT);
  digitalWrite(I2C_POWER_PIN, HIGH);
  delay(100);

  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);

  Serial.println("MPU-6050 with Button Calibration (ESP32 Feather V2)");
  
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) delay(10);
  }
  
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  Serial.println("MPU6050 initialized!");
  
  // Try to load calibration from EEPROM
  if (loadCalibration()) {
    Serial.println("Loaded calibration from memory");
    printCalibrationValues();
  } else {
    Serial.println("No calibration found - using defaults");
  }
  
  Serial.println("\n--- CONTROLS ---");
  Serial.println("Press button once: START calibration");
  Serial.println("Press button again: STOP and save calibration");
  Serial.println("Keep sensor flat and still during calibration\n");
}

void loop() {
  // Check for button press
  if (digitalRead(CALIBRATE_BUTTON_PIN) == LOW) {
    if (millis() - lastButtonPress > debounceDelay) {
      lastButtonPress = millis();
      handleButtonPress();
    }
  }
  
  // Get sensor data
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  if (isCalibrating) {
    // Accumulate samples for calibration
    accelXSum += a.acceleration.x;
    accelYSum += a.acceleration.y;
    accelZSum += a.acceleration.z;
    gyroXSum += g.gyro.x;
    gyroYSum += g.gyro.y;
    gyroZSum += g.gyro.z;
    
    calibrationSamples++;
    
    if (calibrationSamples % 50 == 0) {
      Serial.print("Calibrating... samples: ");
      Serial.println(calibrationSamples);
    }
  } else {
    // Normal operation - apply calibration and calculate orientation
    float accelX = a.acceleration.x - accelOffsetX;
    float accelY = a.acceleration.y - accelOffsetY;
    float accelZ = a.acceleration.z - accelOffsetZ;
    
    // Calculate pitch and roll from accelerometer (in radians)
    float pitchRad = atan2(accelY, sqrt(accelX * accelX + accelZ * accelZ));
    float rollRad = atan2(-accelX, accelZ);
    
    // Convert to degrees
    float pitchDeg = pitchRad * 180.0 / PI;
    float rollDeg = rollRad * 180.0 / PI;
    
    // Normalize to -1.0 to +1.0 range
    // Pitch: -90° to +90° -> -1 to +1
    // Roll: -180° to +180° -> -1 to +1
    float pitchNorm = pitchDeg / 90.0;
    float rollNorm = rollDeg / 180.0;
    
    // Clamp to [-1, 1] range in case of calculation overflow
    pitchNorm = constrain(pitchNorm, -1.0, 1.0);
    rollNorm = constrain(rollNorm, -1.0, 1.0);
    
    // Display normalized pitch and roll
    Serial.print("Pitch: ");
    Serial.print(pitchNorm, 4);
    Serial.print(" | Roll: ");
    Serial.print(rollNorm, 4);
    Serial.print(" | (Pitch°: ");
    Serial.print(pitchDeg, 1);
    Serial.print(", Roll°: ");
    Serial.print(rollDeg, 1);
    Serial.println(")");
  }
  
  delay(10);
}

void handleButtonPress() {
  if (!isCalibrating) {
    // Start calibration
    startCalibration();
  } else {
    // Stop calibration and calculate offsets
    finishCalibration();
  }
}

void startCalibration() {
  Serial.println("\n=== CALIBRATION STARTED ===");
  Serial.println("Keep sensor flat and still!");
  Serial.println("Press button again to finish...\n");
  
  isCalibrating = true;
  calibrationSamples = 0;
  accelXSum = accelYSum = accelZSum = 0;
  gyroXSum = gyroYSum = gyroZSum = 0;
}

void finishCalibration() {
  if (calibrationSamples < 100) {
    Serial.println("\nNot enough samples! Need at least 100.");
    Serial.println("Calibration cancelled.\n");
    isCalibrating = false;
    calibrationSamples = 0;
    return;
  }
  
  Serial.println("\n=== CALCULATING OFFSETS ===");
  
  // Calculate averages
  accelOffsetX = accelXSum / calibrationSamples;
  accelOffsetY = accelYSum / calibrationSamples;
  accelOffsetZ = (accelZSum / calibrationSamples) - 9.81;
  
  gyroOffsetX = gyroXSum / calibrationSamples;
  gyroOffsetY = gyroYSum / calibrationSamples;
  gyroOffsetZ = gyroZSum / calibrationSamples;
  
  // Save to EEPROM
  saveCalibration();
  
  Serial.print("Used ");
  Serial.print(calibrationSamples);
  Serial.println(" samples");
  
  printCalibrationValues();
  
  Serial.println("Calibration saved to memory!");
  Serial.println("=== CALIBRATION COMPLETE ===\n");
  
  isCalibrating = false;
  calibrationSamples = 0;
}

void saveCalibration() {
  CalibrationData data;
  data.accelOffsetX = accelOffsetX;
  data.accelOffsetY = accelOffsetY;
  data.accelOffsetZ = accelOffsetZ;
  data.gyroOffsetX = gyroOffsetX;
  data.gyroOffsetY = gyroOffsetY;
  data.gyroOffsetZ = gyroOffsetZ;
  
  // Write magic number
  EEPROM.put(EEPROM_MAGIC_ADDR, EEPROM_MAGIC);
  // Write calibration data
  EEPROM.put(EEPROM_DATA_ADDR, data);
  // ESP32 requires commit() to actually write to flash
  EEPROM.commit();
}

bool loadCalibration() {
  uint32_t magic;
  EEPROM.get(EEPROM_MAGIC_ADDR, magic);
  
  if (magic != EEPROM_MAGIC) {
    return false; // No valid calibration found
  }
  
  CalibrationData data;
  EEPROM.get(EEPROM_DATA_ADDR, data);
  
  accelOffsetX = data.accelOffsetX;
  accelOffsetY = data.accelOffsetY;
  accelOffsetZ = data.accelOffsetZ;
  gyroOffsetX = data.gyroOffsetX;
  gyroOffsetY = data.gyroOffsetY;
  gyroOffsetZ = data.gyroOffsetZ;
  
  return true;
}

void printCalibrationValues() {
  Serial.println("\nCurrent calibration values:");
  Serial.println("accelOffsetX = " + String(accelOffsetX, 4));
  Serial.println("accelOffsetY = " + String(accelOffsetY, 4));
  Serial.println("accelOffsetZ = " + String(accelOffsetZ, 4));
  Serial.println("gyroOffsetX = " + String(gyroOffsetX, 4));
  Serial.println("gyroOffsetY = " + String(gyroOffsetY, 4));
  Serial.println("gyroOffsetZ = " + String(gyroOffsetZ, 4));
  Serial.println();
}
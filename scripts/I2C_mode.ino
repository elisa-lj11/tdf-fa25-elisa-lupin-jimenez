/*
Date: 5/2021
Author: Elias Santistevan @ SparkFun Electronics
Writing vibration values via I2C to vibrate the motor. 

This vibrates *extremely* vigurously, adhere the motor to something or it will
produce a fault and stop functioning. 

*/

#include <Wire.h>
#include "Haptic_Driver.h"

// Example for SDA on GPIO 23 and SCL on GPIO 19
#define I2C_SDA_PIN 22 
#define I2C_SCL_PIN 20

// Define the specific pin used for I2C/NEOPIXEL Power on the Feather ESP32 V2
// Note: This pin is typically GPIO 15, but using the defined constant is safer
#define I2C_POWER_PIN 2

Haptic_Driver hapDrive;

int event = 0; 

void setup(){

  //Wire.begin();
  
  Serial.begin(115200);
  delay(1000); // Give serial time to initialize

  // Manually enable I2C Power (Specific to Feather ESP32 V2)
  Serial.println("Enabling I2C/STEMMA QT Power (HIGH on GPIO 15).");

  // Set the pin as an output
  pinMode(I2C_POWER_PIN, OUTPUT);
  
  // Set the pin HIGH to ENABLE power to the STEMMA QT port
  digitalWrite(I2C_POWER_PIN, HIGH);
  
  delay(100); // Give power time to stabilize

  // Use the following format for ESP32: 
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);

  if( !hapDrive.begin())
    Serial.println("Could not communicate with Haptic Driver.");
  else
    Serial.println("Qwiic Haptic Driver DA7280 found!");

  if( !hapDrive.defaultMotor() ) 
    Serial.println("Could not set default settings.");

  // Frequency tracking is done by the IC to ensure that the motor is hitting
  // its resonant frequency. I found that restricting the PCB (squeezing)
  // raises an error which stops operation because it can not reach resonance.
  // I disable here to avoid this error. 
  hapDrive.enableFreqTrack(false);

  Serial.println("Setting I2C Operation.");
  hapDrive.setOperationMode(DRO_MODE);
  Serial.println("Ready.");

  delay(1000);

}

void loop(){

  // If uploading often the Haptic Driver IC will throw a fault. Let's
  // clear that error (0x10), just in case.
  //event = hapDrive.getIrqEvent();
  //Serial.print("Interrupt: ");
  //Serial.println(event, HEX);
  //Serial.println("Clearing event.");
  //hapDrive.clearIrq(event);

  // Max value is 127 with acceleration on (default).
  hapDrive.setVibrate(25);
  delay(500); 
  hapDrive.setVibrate(0); 
  delay(500);

}

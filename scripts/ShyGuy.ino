/*
 * ShyGuy
 * Author: Elisa Lupin-Jimenez
 * Based off of UltrasonicServoTest.ino
 * Referenced ChatGPT to generate smoothing solution for servo
 */

#include <Servo.h>
#include <Ultrasonic.h>

/*
 * Pass as a parameter the trigger and echo pin
 */

Ultrasonic ultrasonic(12, 13);
Servo myservo;  // Create servo object to control a servo

float distance;
float rawDistance;
int val;

// Referencing ChatGPT smoothing solution
// Smoothing factor (0.0 - 1.0), lower = smoother
const float alpha = 0.1;  // e.g. 0.1 = heavy smoothing

void setup() {
  myservo.attach(9);  // Attaches the servo on pin 9 to the servo object
  Serial.begin(9600);

  // Initialize smoothed distance to first reading
  rawDistance = ultrasonic.read();
  distance = rawDistance;
}

void loop() {
  // Read new raw distance
  rawDistance = ultrasonic.read();

  // Constrain the reading to a 50 cm maximum
  if (rawDistance > 50) {
    rawDistance = 50;
  }

  // Exponential moving average smoothing (from ChatGPT)
  distance = alpha * rawDistance + (1 - alpha) * distance;
  
  // Print smoothed and raw distances in cm
  Serial.print("Raw Distance: ");
  Serial.println(rawDistance);
  Serial.println("Smoothed: ");
  Serial.println(distance);

  // Scaled for use with the servo (value between 0 and 180)
  val = map(distance, 0, 50, 0, 180);

  // Sets the servo position according to the scaled value
  myservo.write(val);
}

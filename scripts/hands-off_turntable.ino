/*
*  Built off of Makeability_serialIO_v4c_motor.ino
*  Example code control motor movement with data sent from p5.js
*  in p5 posenet tracks positions of ears: tilt head to move motor
*  p5 code here: https://editor.p5js.org/loopstick/sketches/MWZxoSNoP
*  Google Gemini assist with DC motor dead-band: https://g.co/gemini/share/4bd36e495ac7
*/

// Include the Hbridge library -> from: https://github.com/AndreaLombardo/L298N/
#include <L298N.h>

// Pin definition
const unsigned int IN1 = 7;
const unsigned int IN2 = 8;
const unsigned int EN = 9;
int mtrSpd = 0;

// Create one motor instance
L298N motor(EN, IN1, IN2);

// LED stuff
int inc = 1;
int brightness = 10;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication 
  Serial.begin(115200);
  Serial.println("Dr. Sudhu Test Code - Hi !"); // so we know something's working!!!
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  // so we know something's working!!!
  analogWrite(11, 127); 
  delay(300);
  analogWrite(11, 0); 
}

// the loop routine runs over and over again forever:
void loop() {
  // Serial.println("Hello World! - Hi! )");
  // delay(1000);                       // wait for a second

  // Check to see if there is any incoming serial data
  if(Serial.available() > 0){
    // If we're here, then serial data has been received
    // Read data off the serial port until we get to the endline delimeter ('\n')
    // Store all of this data into a string
    String rcvdSerialData = Serial.readStringUntil('\n'); 
    // Echo the data back on serial (for debugging purposes)
    // Serial.print("Arduino Received: '");
    // Serial.print(rcvdSerialData);
    // Serial.println("'");

    int value = rcvdSerialData.toInt();
    // Serial.print(" - convert to Int '");
    // Serial.print(value);
    // Serial.println("'");

    mtrSpd = value;
  } 

    // Tighter dead-band
    if(mtrSpd >= 125 && mtrSpd <= 129){
      motor.stop();
       Serial.print("Arduino STOP'");
       Serial.println("'");
    } else if (mtrSpd > 129){
        motor.forward();
        int fwdSpd = map(mtrSpd, 130, 255, 60, 255);
        motor.setSpeed(fwdSpd);
        //motor.setSpeed(100);
        Serial.println("Arduino forward");Serial.println(fwdSpd);
    } else if (mtrSpd < 125){
        motor.backward();
        int bwdSpd = map(mtrSpd, 0, 124, 255, 60);
        motor.setSpeed(bwdSpd);
        //motor.setSpeed(100);
        Serial.print("Arduino backward: ");Serial.println(bwdSpd);
    }

        // Serial.print("Arduino MtrSpd: '");
        // Serial.print(mtrSpd);
        // Serial.println("'");

}



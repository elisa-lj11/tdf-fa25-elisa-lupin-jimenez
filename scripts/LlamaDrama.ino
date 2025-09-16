/*
  LlamaDrama

  Controls the position of the rotating llama with LED pushbutton control

*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo

const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin = 13;  // the number of the LED pin
const int potPin = A0;  // Analog input pin that the potentiometer is attached to

int buttonState = 0;         // variable for reading the pushbutton status
int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

void setup() {
  // Commented out since I don't need to read serial messages
  // initialize serial communications at 9600 baud rate
	// Serial.begin(9600);

  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  // attaches the servo on pin 9 to the servo object
  myservo.attach(9);

}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }

  sensorValue = analogRead(potPin);  // read the analog in value from the portentiometer
  
  outputValue = map(sensorValue, 0, 1023, 0, 180);   // map it to the range of the analog out:
  
  /*
  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);
  */

  myservo.write(outputValue);                  // sets the servo position according to the scaled value

  // wait 20 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(20);
}
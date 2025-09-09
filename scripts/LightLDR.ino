/*
  HoverBlink

  Turns an LED on when the LDR is hovered.

  Most Arduinos have an on-board LED you can control. 
  On the UNO it is attached to digital pin 13

  This example code is modified from.
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

const int ldrToggleValue = 200;
int led = 13;  // define a variable to hold the pin number of the internal LED

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(led, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);

  // print out the value you read:
  Serial.print("Analog IN A0 value = ");
  Serial.println(sensorValue);

  if (sensorValue > ldrToggleValue)
  {
      digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  }
  else
  {
      digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  }

  delay(20);                   // wait for half a second
}
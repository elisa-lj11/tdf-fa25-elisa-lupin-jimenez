/*
  Matrix

  Blue LED is on by default, switches to red LED when LDR is hovered.

*/

const int ldrToggleValue = 200;
int redLed = 12;   // GPIO slot for red light
int blueLed = 13;  // GPIO slot for blue light

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);

  // initialize LEDs as outputs
  pinMode(redLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);

  if (sensorValue > ldrToggleValue)
  {
      digitalWrite(redLed, HIGH);   // toggle red LED on
      digitalWrite(blueLed, LOW);   // toggle blue LED off
  }
  else
  {
      digitalWrite(blueLed, HIGH);   // toggle blue LED on
      digitalWrite(redLed, LOW);     // toggle red LED off
  }

  delay(20);                         // wait for half a second
}
/*
  ButtonTest

  Writes a push/release message when pressing a pushbutton attached to pin 2.

  Based off of 07a_Button.ino from Arduino guide
  https://github.com/loopstick/ArduinoTutorial/blob/master/examples/07_Button/07a_Button/07a_Button.ino

*/

const int buttonPin = 2;     // the number of the pushbutton pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  //initialize serial communications at 9600 baud rate
	Serial.begin(9600);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    Serial.println("Button is pressed");
  } else {
    Serial.println("Button is released");
  }

  delay(200);
}
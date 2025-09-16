/*
  PotentiometerTest

  Test the reading of the potentiometer

  Based off of https://github.com/loopstick/ArduinoTutorial/blob/master/examples/08_Potentiometer/08c_Pot_AnalogInOutSerial/08c_Pot_AnalogInOutSerial.ino

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogInput
*/

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

void setup() {
  Serial.begin(9600);     // initialize serial communications at 9600 bps:
}

void loop() {
  sensorValue = analogRead(analogInPin);  // read the analog in value from the portentiometer
  
  outputValue = map(sensorValue, 0, 1023, 0, 255);   // map it to the range of the analog out:
  
  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(2);
}
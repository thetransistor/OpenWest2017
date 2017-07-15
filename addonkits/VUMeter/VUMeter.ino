/*
  Analog input, analog output, serial output

 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.

 The circuit:
 * potentiometer connected to analog pin 0.
   Center pin of the potentiometer goes to the analog pin.
   side pins of the potentiometer go to +5V and ground
 * LED connected from digital pin 9 to ground

 created 29 Dec. 2008
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = A3;  // Analog input pin that the potentiometer is attached to
//const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the microphone
int outputValue = 0;        // value output to the PWM (analog out)
int rawValue = 0; // raw value from microphone
int initialValue = 0;
int gainValue = 0;
int gain = 0;
int initial[11];

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  //pinMode(A1, OUTPUT);
  pinMode(A2, INPUT);
  //pinMode(A5, OUTPUT);
  //digitalWrite(A1, HIGH);
  //digitalWrite(A5, LOW);

  //initialValue = analogRead(analogInPin);
  for(int x = 0; x<10; x++){
    initialValue += analogRead(analogInPin);
    delay(10);
  }
  
  initialValue = initialValue/10;

  
}

void loop() {
  // read the analog in value:
  rawValue = analogRead(analogInPin);
  if(rawValue > (initialValue-8)){
    sensorValue = rawValue;
  }
  gainValue = analogRead(A2);
  // map it to the range of the analog out:
  //outputValue = map(sensorValue, 0, 1023, 0, 255);
  // change the analog out value:
  //analogWrite(analogOutPin, outputValue);
  
  gain = map(gainValue, 0, 1023, initialValue, 1023);
  outputValue = map(sensorValue, initialValue-8, gain, 0, 8);
  
  // print the results to the serial monitor:
  //Serial.print("sensor = ");
  Serial.print(initialValue);
  Serial.print(" ");
  Serial.print(sensorValue);
  Serial.print(" ");
  Serial.println(gain);

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(50);

  
  //outputValue = 4;

  if(outputValue > 0) {
    digitalWrite(2, HIGH);
  } else {
    digitalWrite(2, LOW);
  }
  if(outputValue > 1) {
    digitalWrite(3, HIGH);
  } else {
    digitalWrite(3, LOW);
  }
  if(outputValue > 2) {
    digitalWrite(4, HIGH);
  } else {
    digitalWrite(4, LOW);
  }
  if(outputValue > 3) {
    digitalWrite(5, HIGH);
  } else {
    digitalWrite(5, LOW);
  }
  if(outputValue > 4) {
    digitalWrite(6, HIGH);
  } else {
    digitalWrite(6, LOW);
  }
  if(outputValue > 5) {
    digitalWrite(7, HIGH);
  } else {
    digitalWrite(7, LOW);
  }
  if(outputValue > 6) {
    digitalWrite(8, HIGH);
  } else {
    digitalWrite(8, LOW);
  }
  if(outputValue > 7) {
    digitalWrite(9, HIGH);
  } else {
    digitalWrite(9, LOW);
  }
  
}

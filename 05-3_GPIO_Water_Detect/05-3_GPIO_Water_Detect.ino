/* water-level sensor example */

// constants won't change. They're used here to set pin numbers:
const int waterPin = 2;     // the number of the water-level pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int waterState = 0;         // variable for reading the water-level status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the water-level pin as an input:
  pinMode(waterPin, INPUT_PULLUP);
}

void loop() {
  // read the state of the water-level value:
  waterState = digitalRead(waterPin);

  // check if the water-level reaches the threshold. If it is, the waterState is HIGH:
  if (waterState == LOW) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
}

/*
 * Find out max sound value (Analog input)
*/

// constants won't change. They're used here to set pin numbers:
const int soundAnalogPin = A2;
const int ledPin =  LED_BUILTIN;      // the number of the LED pin

// variables will change:
int soundAnalogValue;
int maxValue = 0;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  while(!Serial);
  Serial.println("start (analog)!");
}

void loop() {
  soundAnalogValue = analogRead(soundAnalogPin);
  if(soundAnalogValue > maxValue) {
    maxValue = soundAnalogValue;
    Serial.println(soundAnalogValue);    
  }
}

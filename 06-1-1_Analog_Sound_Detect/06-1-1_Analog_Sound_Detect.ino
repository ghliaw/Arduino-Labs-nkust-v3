/*
 * Toggle LED ON/OFF by sound (Analog)
*/
#define DO_NOTHING_INTERVAL 50 //ms
#define SOUND_THRESHOLD 0

// constants won't change. They're used here to set pin numbers:
const int soundAnalogPin = A2;
const int ledPin =  LED_BUILTIN;      // the number of the LED pin

// variables will change:
int ledState = 0;
bool allowCheck = true;
unsigned long startDoNothingTime;
int soundAnalogValue;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  while(!Serial);
  Serial.println("start (analog)!");
}

void loop() {
  if(allowCheck) {
    soundAnalogValue = analogRead(soundAnalogPin);
    if(soundAnalogValue > SOUND_THRESHOLD) {
      Serial.print("detected: ");
      Serial.println(soundAnalogValue);
      ledState = !ledState;
      digitalWrite(ledPin, ledState);
      allowCheck = false;
      startDoNothingTime = millis();
    }
  }
  else {
    if((millis()-startDoNothingTime) >= DO_NOTHING_INTERVAL) allowCheck = true;
  }
}

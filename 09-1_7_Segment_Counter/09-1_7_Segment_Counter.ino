#include "SevSeg.h"

#define STATE_INPUT 1
#define STATE_COUNT 2

SevSeg sevseg; //Instantiate a seven segment controller object
int state;

void setup() {
  Serial.begin(115200);
  byte numDigits = 4;
  byte digitPins[] = {8, 12, 13, 2};
  byte segmentPins[] = {9, 11, 4, 6, 7, 10, 3, 5};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_ANODE; // 共陽極：COMMON_ANODE；共陰極：COMMON_CATHODE 
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected
  
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(100);
  state = STATE_INPUT;
}

void loop() {
  static int deciSeconds = 0;
  static char buf[10];
  static int  length = 0;
  int incoming_byte;
  static unsigned long current, last, last2;
  static int target; 

  if(state == STATE_INPUT) {
    sevseg.setNumber(0, 0);
    if(Serial.available() > 0) { // check if there is incoming data
      incoming_byte = Serial.read();  // read the incoming byte
      buf[length++] = incoming_byte;  // put the incoming byte to string buffer
      if(incoming_byte == '\n') { // check if LF is incoming
        // append '\0' to buf[] as the end of the string
        buf[length++] = '\0';
        // do job
        target = atoi(buf);
        if(target<=0 || target>999) Serial.println("Out of range (1-999)");
        else {
          Serial.print("Start: ");
          Serial.println(target);
          state = STATE_COUNT;
          target = target*10;
          sevseg.setNumber(target,1);
          last = millis();
          last2 = millis();
        }
        length = 0;
      }
    }
  }
  else if (state == STATE_COUNT) {
    current = millis();
    if (current - last >= 100) {
      last = current;
      target -= 1;
      if(target%10==0) Serial.println(target/10);
      if(target==0) {
        sevseg.setNumber(0, 0);
        state = STATE_INPUT;
      }
      else sevseg.setNumber(target, 1);
    }
  }

  sevseg.refreshDisplay(); // Must run repeatedly
}
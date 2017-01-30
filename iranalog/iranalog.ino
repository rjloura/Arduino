/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

int RECV_PIN = 11;
int analogPin = 4;
int val = 0;
int oldval = 0;

IRrecv irrecv(RECV_PIN);

decode_results results;

int YELLOW = 2;
int BLUE = 3;

int BLUE_STATE = LOW;
int YELLOW_STATE = LOW;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(YELLOW, OUTPUT);    
  pinMode(BLUE, OUTPUT);    

}

void loop() {
  val = analogRead(analogPin);
  Serial.println(val);
/*
  if (val != oldval) {
    oldval = val;
    if (BLUE_STATE == HIGH) {
      BLUE_STATE = LOW;
    } else {
      BLUE_STATE = HIGH;
    }
    digitalWrite(BLUE, BLUE_STATE);
  }
  */
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);

    if (results.value == 0xFF6897) {
      if (YELLOW_STATE == HIGH) {
        YELLOW_STATE = LOW;
      } else {
        YELLOW_STATE = HIGH;
      }
      digitalWrite(YELLOW, YELLOW_STATE);
    } else if (results.value == 0xFF9867) {
      if (BLUE_STATE == HIGH) {
        BLUE_STATE = LOW;
      } else {
        BLUE_STATE = HIGH;
      }
      digitalWrite(BLUE, BLUE_STATE);
    }
    irrecv.resume(); // Receive the next value
  }
  delay(200);
  //delay(100);
}

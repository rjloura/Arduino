/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;

int YELLOW = 2;
int BLUE = 3;
int LIGHTS = 4;

int BLUE_STATE = LOW;
int YELLOW_STATE = LOW;
int LIGHTS_STATE = LOW;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(YELLOW, OUTPUT);    
  pinMode(BLUE, OUTPUT);
  pinMode(LIGHTS, OUTPUT);    

}

void loop() {
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
    } else if (results.value == 0xFFB04F) {
      if (LIGHTS_STATE == HIGH) {
        LIGHTS_STATE = LOW;
      } else {
        LIGHTS_STATE = HIGH;
      }
      digitalWrite(LIGHTS, LIGHTS_STATE);
    } else if (results.value == 0xFFA857) {
      for (int i = 0; i < 10; i++) {
        digitalWrite(LIGHTS, HIGH);

        digitalWrite(BLUE, HIGH);

        digitalWrite(YELLOW, HIGH);
        delay(40);
        digitalWrite(LIGHTS, LOW);
        digitalWrite(BLUE, LOW);
        digitalWrite(YELLOW, LOW);
        delay(40);
      }
    } else if (results.value == 0xFF629D) {
      for (int i = 0; i < 2; i++) {
        digitalWrite(LIGHTS, HIGH);
                delay(300);

        digitalWrite(BLUE, HIGH);
        delay(300);

        digitalWrite(YELLOW, HIGH);
        delay(300);
        digitalWrite(LIGHTS, LOW);
        digitalWrite(BLUE, LOW);
        digitalWrite(YELLOW, LOW);
        delay(100);
      }
    }
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}

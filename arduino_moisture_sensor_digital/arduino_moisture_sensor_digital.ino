
/* RX pin on ESP8266 */
int digitalPin = 3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(digitalPin, INPUT);
}

void loop() {

  /*
   * High == Dry
   * Low == Wet
   */
  if (digitalRead(digitalPin) == HIGH)
    Serial.println("Dry");
  else if (digitalRead(digitalPin) == LOW)
    Serial.println("Wet");
  else
    Serial.println("Error");

  delay(1000);
}

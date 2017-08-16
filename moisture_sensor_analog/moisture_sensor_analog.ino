
/* A0 pin on ESP8266 */
int analogPin = A0;
int moisture;
int percentage;

/*
 * The mapping depends on how the sensitivity is set with the blue dial.
 */
int map_high = 550;
int map_low = 1000;

void setup() {
  Serial.begin(9600);
}

void loop() {

  moisture = analogRead(analogPin);
  Serial.print("Raw: ");
  Serial.print(moisture);

  percentage = map(moisture, map_low, map_high, 0, 100);
  Serial.print(" | Percentage: ");
  Serial.print(percentage);
  Serial.println("%");
  
  delay(1000);
}

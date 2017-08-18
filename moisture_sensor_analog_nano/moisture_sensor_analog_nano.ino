
int analogPin = A0;
int moisture;
int percentage;

int map_low = 686;
int map_high = 350;

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

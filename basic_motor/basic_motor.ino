#define R_MOTOR_H 8
#define R_MOTOR_L 9
#define R_MOTOR_DRIVE 10

#define L_MOTOR_H 6
#define L_MOTOR_L 7
#define L_MOTOR_DRIVE 5

void setup() {
  pinMode(R_MOTOR_H, OUTPUT);
  pinMode(R_MOTOR_L, OUTPUT);
  pinMode(R_MOTOR_DRIVE, OUTPUT);
}

void loop() {

  digitalWrite(L_MOTOR_H, HIGH);
  digitalWrite(L_MOTOR_L, LOW);
  analogWrite(L_MOTOR_DRIVE, 250);
  digitalWrite(R_MOTOR_H, HIGH);
  digitalWrite(R_MOTOR_L, LOW);
  analogWrite(R_MOTOR_DRIVE, 250);

  delay(700);

  digitalWrite(R_MOTOR_H, LOW);
  digitalWrite(R_MOTOR_L, HIGH);
  digitalWrite(L_MOTOR_H, LOW);
  digitalWrite(L_MOTOR_L, HIGH);
  delay(700);
  

}

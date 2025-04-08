int E1 = 10;
int M1 = 12;
int E2 = 11;
int M2 = 13;

void setup() {
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);


}

void loop() {
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  analogWrite(E1, 150);
  analogWrite(E2, 0);
  delay(2000);
  digitalWrite(M1, LOW);
  digitalWrite(M2, HIGH);
  analogWrite(E1, 150);
  analogWrite(E2, 0);
  delay(2000);

  analogWrite(E1, 0);
  analogWrite(E2, 0);
  delay(2000);
  
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  analogWrite(E1, 90);
  analogWrite(E2, 250);
  delay(2000);
  digitalWrite(M1, HIGH);
  digitalWrite(M2, LOW);
  analogWrite(E1, 250);
  analogWrite(E2, 90);
  delay(2000);

  analogWrite(E1, 0);
  analogWrite(E2, 0);
  delay(12000);

}
void setup() {
  pinMode(6, INPUT);
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(A0);
  int limit = digitalRead(6);
  Serial.print("analog="); Serial.println(value);
  Serial.print("digital="); Serial.println(limit);
  Serial.println();
  delay(1000);
}

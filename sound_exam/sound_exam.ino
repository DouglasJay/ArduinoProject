void setup() {
  Serial.begin(9600);
  pinMode(7, INPUT);
}

void loop() {
  int sensorstate = digitalRead(8);
  int value = analogRead(A1);
  Serial.println(value);
  delay(1000);
  if (sensorstate == HIGH) {
    Serial.println("HIGH");
  }
}

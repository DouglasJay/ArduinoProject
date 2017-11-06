void setup() {
  Serial.begin(9600);
  pinMode(5, INPUT);
}

void loop() {
  int value = digitalRead(5);
  Serial.println(value);
  delay(1000);
}

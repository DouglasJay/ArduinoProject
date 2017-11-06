void setup() {
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensor = digitalRead(2);
  if (sensor == HIGH) digitalWrite(3, HIGH);
  else digitalWrite(3, LOW);
  Serial.println(sensor);
  delay(1000);
}

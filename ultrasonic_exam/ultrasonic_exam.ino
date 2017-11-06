int duration1 = 0, duration2 = 0;
void setup() {
  pinMode(2, OUTPUT); pinMode(3, INPUT);
  pinMode(4, OUTPUT); pinMode(5, INPUT);
  Serial.begin(960);
}

void loop() {
  digitalWrite(2, LOW); delayMicroseconds(2);
  digitalWrite(2, HIGH); delayMicroseconds(10);
  digitalWrite(2, LOW); duration1 = pulseIn(3, HIGH);
  long distance1 = distance(duration1);
  Serial.print(duration1); Serial.print(" "); Serial.println(distance1);
  delay(1000);
  digitalWrite(4, LOW); delayMicroseconds(2);
  digitalWrite(4, HIGH); delayMicroseconds(10);
  digitalWrite(4, LOW); duration2 = pulseIn(5, HIGH);  
  long distance2 = distance(duration2);
  Serial.print(duration2); Serial.print(" "); Serial.println(distance2);
  delay(1000);
  Serial.println();
}
long distance(long time) { return ((time/2.9)/2); }


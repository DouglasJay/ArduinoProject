void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);  
}

void loop() {
  int pir = digitalRead(2);
  int sound = digitalRead(3);
  int cds = digitalRead(4);
  int value = analogRead(A0);
  if (pir == 1) {
    digitalWrite(8, HIGH);    
} else {                    
    digitalWrite(8, LOW);    
}
if (cds == 1) {    
    digitalWrite(9, HIGH);    
} else {                    
    digitalWrite(9, LOW);
}
if (value >100) {    
    digitalWrite(10, HIGH);    
} else {  
    digitalWrite(10, LOW);
}
if (pir == 1 && cds == 1 && value >100) {
    digitalWrite(5, HIGH);    
} else {                
    digitalWrite(5, LOW);
}
}

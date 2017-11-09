#include <SoftwareSerial.h>
SoftwareSerial btSerial(2,3); //TxD,RxD

void setup() {
  Serial.begin(9600); btSerial.begin(9600); //pinMode(4, OUTPUT);
}

void loop() {
  if (btSerial.available()) Serial.write(btSerial.read());
  if (Serial.available()) btSerial.write(Serial.read());
}
/* int value = analogRead(0); Serial.println(value);
 *  btSerial.println(value); delay(500);
 */

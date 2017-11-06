#include "DHT11.h"
DHT11 dht11(4);
void setup() {
  Serial.begin(9600);
}

void loop() {
  float temperature, humidity;
  int err = dht11.read(humidity, temperature);
  if (err ==0) {
    Serial.print("humidity="); Serial.println(humidity);
    Serial.print("temperature="); Serial.println(temperature);
  }
  delay(1000);
}

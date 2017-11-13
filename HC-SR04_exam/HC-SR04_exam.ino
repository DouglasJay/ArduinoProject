int echoPin = 8;
int trigPin = 9;
//초음파 센서의 핀번호를 설정한다.

void setup(){
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
// trig를 출력모드로 설정, echo를 입력모드로 설정
}

void loop(){
  float duration;
  int distance;
  char signal = 'A';
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  // 초음파를 보낸다. 다 보내면 echo가 HIGH 상태로 대기하게 된다.
  
  duration = pulseIn(echoPin, HIGH); // echoPin 이 HIGH를 유지한 시간을 저장 한다.
  distance = ((float)(340 * duration) / 10000) / 2;  // HIGH 였을 때 시간(초음파가 보냈다가 다시 들어온 시간)을 가지고 거리를 계산 한다.
  
  if(distance < 10) { //인지한 거리가 100이하로 측정될 경우 signal을 zigbee통신을 통해 전송한다.
    Serial.print(signal);
  }
  
  delay(500);
}

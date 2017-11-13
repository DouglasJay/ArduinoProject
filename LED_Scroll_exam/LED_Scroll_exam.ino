/* 
 VCC                      +5V
 DIN                      MOSI (Pin 11)
 LOAD                     pinCS  (Pin 10)
 CLK                      SCK (Pin 13)
 GND                      Gnd 
*/

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

int pinCS = 10; 
int numberOfHorizontalDisplays = 4;
int numberOfVerticalDisplays = 1;

//초음파 센서의 핀번호를 설정
int echoPin = 8;
int trigPin = 9;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);
int scrollspeed = 200; // Default scrollspeed (milliseconds)

int spacer = 1;  // 문자열 사이 공백
int width = 5 + spacer; // 5 pixels
boolean inChar = false, NewData = false, pause = false;
boolean dataAvailable = false;
char inputString[512];
int count = 0, BTvalue = 5;


void setup() {

  matrix.setIntensity(1); // 0~15 밝기
  for (int i = 0; i < numberOfHorizontalDisplays; i++) {
  matrix.setPosition(i, numberOfHorizontalDisplays-i-1, 0);
}
  /*matrix.setRotation(0, 2);    // 처음 디스플레이 업다운
  //matrix.setRotation(3, 2);    // 마지막 디스플레이 업다운*/
  matrix.fillScreen(0);
  matrix.write();
  Serial.begin(9600);
  
  // pin 2 에 인터럽트 0 실행
  pinMode(2, INPUT);
  digitalWrite(2, LOW);
  attachInterrupt(0, serialInterrupt, CHANGE);

  // trig를 출력모드로 설정, echo를 입력모드로 설정
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);  
}

void loop(){
  if(dataAvailable){
  display_data();
 } 
  float duration;
  int distance;
  char signal = 'A';
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  // 초음파 송신 후 보내지면 echo가 HIGH 상태로 대기
  
  duration = pulseIn(echoPin, HIGH); // echoPin 이 HIGH를 유지한 시간을 저장
  distance = ((float)(340 * duration) / 10000) / 2;  // HIGH 였을 때 시간(초음파가 보냈다가 다시 들어온 시간)을 가지고 거리를 계산
  
  if(distance < 10) { //인지한 거리가 10이하로 측정될 경우 signal을 bluetooth통신을 통해 전송
    Serial.print(signal);
  }  
  delay(500);  
 
}

void display_data(){
  for ( int i = 0 ; i < width * count + matrix.width() - 1 - spacer; i++ ) {

    matrix.fillScreen(0);

    int letter = i / width;
    int x = (matrix.width() - 1) - i % width;
    int y = (matrix.height() - 8) / 2; // center the text vertically

    while ( x + width - spacer >= 0 && letter >= 0 ) {
      if ( letter < count ) {
        matrix.drawChar(x, y, inputString[letter], HIGH, LOW, 1);
      }

      letter--;
      x -= width;
    }
    matrix.write(); // bitmap 송신
    if(!dataAvailable){
      i = width * count + matrix.width() - 1 - spacer; 
      matrix.fillScreen(LOW);
      matrix.write();
    }
    if(NewData){
      i = 0; 
      matrix.fillScreen(LOW);
      matrix.write();
      NewData = false;
    }
    while(pause == true){
      delay(0);
    } // 멈춤 명령
    
    delay(scrollspeed);
  }
}

volatile boolean inService = false;

void serialInterrupt(){  
  if (inService) return;  
  inService = true;  
  
  interrupts();
  while(!Serial.available());
  while (Serial.available()) {
     char ch = Serial.read();
     if(ch =='('){
       count = 0;
       inChar = true;
       
       while(inChar){
         if (Serial.available()) {
           ch = Serial.read();
           if(ch == ')'){
             inChar = false;
             dataAvailable = true;
            } else{
             inputString[count] = ch;
             count++;
           }
           if(count > 0) {
             NewData = true;
           }
         }
       }
     }  
     
     if(ch =='/'){   // 커멘드 모드
       inChar = true;
       while(inChar){
         if (Serial.available()) {
           ch = Serial.read();
           // '/+' 밝기 상승
           if(ch == '+'){
             if(BTvalue < 15) {
               BTvalue ++;
               matrix.setIntensity(BTvalue);
              }
             break;
           }  
           // '/-' 밝기 하락           
           if(ch == '-'){
            if(BTvalue > 0){
             BTvalue --;
             matrix.setIntensity(BTvalue);
            }
            break;
           }    

           // '/>' 스크롤 스피드 다운
           if(ch == '>'){
             if(scrollspeed < 500) {
               scrollspeed = scrollspeed + 50;
             }
             break;
           }  
           // '/<' 스크롤 스피드 업           
           if(ch == '<'){
            if(scrollspeed > 50){
             scrollspeed=scrollspeed-50;
            }
            break;
           }   

           // '/e' 삭제           
           if(ch == 'e'){
            dataAvailable = false;
             break; 
           }

           // '/u' 초음파센서            
           /*if(ch == 'u'){
            dataAvailable = false;
             break; 
           }*/

           // '/t' 택트스위치           
           /*if(ch == 't'){
            dataAvailable = false;
             break; 
           }*/
           
           // '/p' 멈춤           
           if(ch == 'p'){
             if(pause == false){
               pause = true;
             } 
             else {
               pause = false;
             } 
             break; 
           }
           
           else {
            break;  // 나머지 커멘드 
           }
           
           
         }
       }
     }  // if(ch == '!')

    
  }  // while(serial.available)
  inService = false;
}




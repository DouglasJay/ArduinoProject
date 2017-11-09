#include <SoftwareSerial.h>

//#include <SoftwareSerial.h>

SoftwareSerial softwareSerial(2, 3); // RX, TX


void printUsage(){
  softwareSerial.println("사용가능한 명령어\n");
  softwareSerial.println("1 : LED 켜기");
  softwareSerial.println("2 : LED 끄기");
  softwareSerial.println("S : LED 상태정보\n\n");
}

void setup() {

  softwareSerial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() { 

  if (softwareSerial.available() > 0 ) {


    char command = softwareSerial.read();
    int ledStatus = digitalRead(LED_BUILTIN);

    switch (command){

      case '1':
      
        if (ledStatus == LOW){
          digitalWrite(LED_BUILTIN, HIGH);
          softwareSerial.println("LED가 켜졌습니다.\n");
        }
        else{
          softwareSerial.println("이미 LED가 켜져있습니다.\n");
        }
        break;

      case '2':
      
        if (ledStatus == HIGH){
          digitalWrite(LED_BUILTIN, LOW);
          softwareSerial.println("LED가 꺼졌습니다.\n");
        }
        else{
          softwareSerial.println("이미 LED가 꺼져있습니다.\n");
        }
        break;

      case 'S':
      case 's':
          
        if (ledStatus == LOW){
          softwareSerial.println("LED 상태: 꺼짐\n");
        }
        else {
          softwareSerial.println("LED 상태: 켜짐\n");
        }
        break;
      
     default:
     
          softwareSerial.println( (char)command, HEX);
          printUsage();

        break;
      
    }      
  }
}

#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); //블루투스의 Tx, Rx핀을 2번 3번핀으로 설정

int sensorValue=0;
int speedValue=0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600) ; 
mySerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
sensorValue = analogRead(A0);
speedValue = analogRead(A1);
//Serial.print(sensorValue);
mySerial.print("R,");
mySerial.print(sensorValue);
mySerial.println("*");
Serial.println(speedValue/5);
mySerial.print("P,"); 
mySerial.print(speedValue/5);
mySerial.println("*");
delay(300);
}

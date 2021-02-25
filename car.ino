//R,100*
//카

#include <Servo.h>
#include <SoftwareSerial.h>
#define ENA 3
#define EN1 10
#define EN2 11

SoftwareSerial mySerial(4, 5); //블루투스의 Tx, Rx핀을 2번 3번핀으로 설정

Servo myservo;  // create servo object to control a servo

int potpin = 0;  // analog pin used to connect the potentiometer
int val;   
String ledString=" ";
String serArray[5];
int16_t R =100;
int16_t P ;
String Y ;
String T ;
int16_t N ;
int Motor_speed=0; // 모터 속도 PWM 100으로 설정 0~255
void setup() {
  // put your setup code here, to run once:
  digitalWrite(EN1, HIGH);   // 모터A 설정 
digitalWrite(EN2, LOW);  
analogWrite(ENA, Motor_speed);  
myservo.attach(9); 
Serial.begin(9600) ; 
mySerial.begin(9600);
}

void loop() {
  
  // put your main code here, to run repeatedly:
control();
int si=R/20+25;
myservo.write(si);
Serial.println(si);
if(P>100)
{
  digitalWrite(EN1, HIGH);   // 모터A 설정 
digitalWrite(EN2, LOW);  
analogWrite(ENA, P-100); 
}
if(P<=100)
{
  digitalWrite(EN2, HIGH);   // 모터A 설정 
  digitalWrite(EN1, LOW);  
  analogWrite(ENA, 100-P); 
}

    
}
void control()
{
   if(mySerial.available()){
    
    char ch = mySerial.read();
    ledString+=ch;
    if(ch == '*'){
      //Serial.print('2');
      if(ledString.length()>0){
        int startCMD =0;
        int tmpcnt=0;
        int idx;
        String tmpString=ledString;
        tmpString.trim();
        while(tmpString.length()>0){
          idx = tmpString.indexOf(",");
          if(idx == -1){
            serArray[tmpcnt]= tmpString;
            serArray[tmpcnt].trim();
            tmpcnt++;
            break;
          }
          serArray[tmpcnt] = tmpString.substring(0,idx);
          tmpString = tmpString.substring(idx+1);
          tmpString.trim();
          serArray[tmpcnt].trim();
          tmpcnt++;
        }
        if(serArray[0]=="T"){
          T = serArray[1];
          Serial.println(T);
      
        }
        if(serArray[0]=="R"){
          R= serArray[1].toInt();
          Serial.println(R);
        }
        if(serArray[0]=="P"){
          P = serArray[1].toInt();
        }
        if(serArray[0]=="Y"){
         Y = serArray[1];
         Serial.println(Y);
        }
        if(serArray[0]=="N"){
         N = serArray[1].toInt();
         Serial.println(N);
        }
     
      }
      ledString = "";
     
    }
  }
}

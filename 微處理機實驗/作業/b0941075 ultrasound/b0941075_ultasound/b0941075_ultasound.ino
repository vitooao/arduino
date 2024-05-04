#include <Servo.h>

Servo wifiServo;
Servo USServo1;
Servo USServo2;
int wifiServoValue;
#define WIFI_SERVO_PIN 17
#define US_SERVO_1_PIN 18
#define US_SERVO_2_PIN 19
  
const byte trigPin = 9;  // 超音波模組的觸發腳
const int echoPin = 10;    // 超音波模組的接收腳
unsigned long d;          // 儲存高脈衝的持續時間

unsigned long ping() {
  digitalWrite(trigPin, HIGH);   // 觸發腳設定成高電位
  delayMicroseconds(5);          // 持續 5 微秒
  digitalWrite(trigPin, LOW);    // 觸發腳設定成低電位
 
  return pulseIn(echoPin, HIGH); // 傳回高脈衝的持續時間
}
int x,y;
int i,j;
int a,b;
int c=1500;
void setup()
{
  Serial.begin (9600); 
  pinMode(trigPin, OUTPUT);  // 觸發腳設定成「輸出」
  pinMode(echoPin, INPUT);   // 接收腳設定成「輸入」
  delay(1000);
  wifiServo.attach(WIFI_SERVO_PIN , 500 , 2400);
  USServo1.attach(US_SERVO_1_PIN , 500 , 2400);
  USServo2.attach(US_SERVO_2_PIN , 500 , 2400);
  wifiServo.write(90);
  USServo1.write(0);   //從0,0開始
  USServo2.write(0);
  delay(1000);
    
}

void loop()
{
  for(j=0;j<=9;j++){    //直的(0~90)，再往下會測到地板
    y=j*10;
    USServo2.write(y);
    for(i=0;i<=9;i++){
      x=i*20;
      USServo1.write(x);   //橫的(0~180)
      A();
      if (d<=c){ //當目前的d比之前的小，紀錄當前的x和y
        c=d;
        a=x;
        b=y;
        }
      delay(1000);      
      }
}
USServo2.write(b);
USServo1.write(a);
Serial.print("closest distance is ");
  Serial.print(c);
  Serial.println(" cm");
delay(10000);
}

void A(){
  d = ping() / 58; 
  Serial.print("distance ");
  Serial.print(d);
  Serial.println(" cm");

}

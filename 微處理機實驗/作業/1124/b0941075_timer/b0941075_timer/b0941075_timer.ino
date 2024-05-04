#include <LiquidCrystal.h>
//使用到的PIN腳
const int pin_RS = 8; 
const int pin_EN = 9; 
const int pin_D4 = 4; 
const int pin_D5 = 5; 
const int pin_D6 = 6; 
const int pin_D7 = 7; 
//填入正確的PIN腳，建立LCD物件
LiquidCrystal lcd( pin_RS,  pin_EN,  pin_D4,  pin_D5,  pin_D6,  pin_D7);

const byte trigPin = 13;  // 超音波模組的觸發腳
const int echoPin = 12;    // 超音波模組的接收腳
unsigned long d;          // 儲存高脈衝的持續時間

unsigned long ping() {
  digitalWrite(trigPin, HIGH);   // 觸發腳設定成高電位
  delayMicroseconds(5);          // 持續 5 微秒
  digitalWrite(trigPin, LOW);    // 觸發腳設定成低電位
 
  return pulseIn(echoPin, HIGH); // 傳回高脈衝的持續時間
}
#include "Timer.h" 

Timer t;  //建立Timer物件
int count=0;


void setup() {
 lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT);  // 觸發腳設定成「輸出」
  pinMode(echoPin, INPUT);   // 接收腳設定成「輸入」
 Serial.begin(9600);
 t.every(5000,A);         // 初始化序列埠
}
void loop() {
  t.update();
  Serial.println(d);
   lcd.setCursor(0,0);
   lcd.print("Distance");
   lcd.setCursor(13,0);
   lcd.print("cm");
} 
void A(){
  d = ping() / 58; 
   lcd.clear();    
    count++;   
    B();
}
void B(){
  lcd.setCursor(9,0);
   lcd.print(d);}

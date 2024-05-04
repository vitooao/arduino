//
// Title       : 範例三
// Description : 使用 Arduino 接收攝像頭模組資料並回傳
//
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
int counter = 0;

int a,b;

//
//  Motor
//
const int PWM_R1 = 11; ///<Motor1 Speed
const int PWM_L1 = 6;  ///<Motor2 Speed
const int PWM_R2 = 5;  ///<Motor3 Speed
const int PWM_L2 = 3;  ///<Motor4 Speed

const int DIR_R1 = 8; ///<Motor1 Direction
const int DIR_L1 = 7; ///<Motor2 Direction
const int DIR_R2 = 4; ///<Motor3 Direction
const int DIR_L2 = 2; ///<Motor4 Direction

int PWM_SPEED = 80*0.5;

//
//  Ultrasonic sensor
//

unsigned long ping() {
  digitalWrite(trigPin, HIGH);   // 觸發腳設定成高電位
  delayMicroseconds(5);          // 持續 5 微秒
  digitalWrite(trigPin, LOW);    // 觸發腳設定成低電位
 
  return pulseIn(echoPin, HIGH); // 傳回高脈衝的持續時間
}

void setup()
{
  pinMode(PWM_R1, OUTPUT);
  pinMode(PWM_L1, OUTPUT);
  pinMode(PWM_R2, OUTPUT);
  pinMode(PWM_L2, OUTPUT);
  pinMode(DIR_R1, OUTPUT);
  pinMode(DIR_L1, OUTPUT);
  pinMode(DIR_R2, OUTPUT);
  pinMode(DIR_L2, OUTPUT);

  pinMode(trigPin, OUTPUT);  // 觸發腳設定成「輸出」
  pinMode(echoPin, INPUT);   // 接收腳設定成「輸入」

  Serial.begin(9600);

  wifiServo.attach(WIFI_SERVO_PIN , 500 , 2400);
  USServo1.attach(US_SERVO_1_PIN , 500 , 2400);
  USServo2.attach(US_SERVO_2_PIN , 500 , 2400);
  wifiServo.write(90);
  USServo1.write(90); //下面
  USServo2.write(90);
  delay(100);
}

void loop()
{ run();
  a=100;
  b=100;
  
 //Serial.print(a);
  scan();
  A();
  
  scan2();
  B();
  }
  


void scan()
{for(int i = 0;i <= 15;i++)
  {
    USServo1.write(90-i*3);
    d = ping() / 58;       // 把高脈衝時間值換算成公分單位
      if(d < a)
        {a=d;}
        Serial.println(d);
    delay(5); 
  }
  for(int i = 0;i <= 15;i++)
  {
    USServo1.write(45+i*3);
    d = ping() / 58;       // 把高脈衝時間值換算成公分單位
      if(d < a)
        {a=d;}
        Serial.println(d);
    delay(5); 
  }
  
  
  
  
   
}

void scan2(){
  for(int i = 0;i <= 15;i++){
  USServo1.write(90+i*3);
    d = ping() / 58;       // 把高脈衝時間值換算成公分單位
      if(d < b)
        {b=d;}
    delay(5); 
  }
  for(int i = 0;i <= 15;i++)
  {
    USServo1.write(135-i*3);
    d = ping() / 58;       // 把高脈衝時間值換算成公分單位
      if(d < b)
        {b=d;}
    delay(5); }}
void A(){
  if(a<15){
    brake();
      delay(50);
    right();
    delay(800);
    a=100;
    run();
    delay(300);
    }
  }
    void B(){
  if(b<15){
    brake();
      delay(50);
    left();
    delay(800);
    b=100;
    run();
    delay(300);
    }
  }
void run()
{
  digitalWrite(DIR_R1, LOW);
  analogWrite(PWM_R1, PWM_SPEED+30*0.5);
  digitalWrite(DIR_L1, LOW);
  analogWrite(PWM_L1, PWM_SPEED+20*0.5);
  digitalWrite(DIR_R2, LOW);
  analogWrite(PWM_R2, PWM_SPEED+20*0.5);
  digitalWrite(DIR_L2, LOW);
  analogWrite(PWM_L2, PWM_SPEED+20*0.5);
}

void brake()
{

  digitalWrite(DIR_R1, LOW);
  analogWrite(PWM_R1, 0);
  digitalWrite(DIR_L1, LOW);
  analogWrite(PWM_L1, 0);
  digitalWrite(DIR_R2, LOW);
  analogWrite(PWM_R2, 0);
  digitalWrite(DIR_L2, LOW);
  analogWrite(PWM_L2, 0);
}

void right()
{
  digitalWrite(DIR_R1, HIGH);
  analogWrite(PWM_R1, PWM_SPEED+50*0.5);
  digitalWrite(DIR_L1, LOW);
  analogWrite(PWM_L1, PWM_SPEED+60*0.5);
  digitalWrite(DIR_R2, LOW);
  analogWrite(PWM_R2, PWM_SPEED+70*0.5);
  digitalWrite(DIR_L2, HIGH);
  analogWrite(PWM_L2, PWM_SPEED+60*0.5);
}

void left()
{
  digitalWrite(DIR_R1, LOW);
  analogWrite(PWM_R1, PWM_SPEED+55*0.5);
  digitalWrite(DIR_L1, HIGH);
  analogWrite(PWM_L1, PWM_SPEED+65*0.5);
  digitalWrite(DIR_R2, HIGH);
  analogWrite(PWM_R2, PWM_SPEED+60*0.5);
  digitalWrite(DIR_L2, LOW);
  analogWrite(PWM_L2, PWM_SPEED+55*0.5);
}

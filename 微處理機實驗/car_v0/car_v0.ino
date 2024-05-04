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
int c1 = 0;
int c2 = 0;
int c3 = 0;

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

int PWM_SPEED = 80*0.7;

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
  Serial.println("Ready");

  wifiServo.attach(WIFI_SERVO_PIN , 500 , 2400);
  USServo1.attach(US_SERVO_1_PIN , 500 , 2400);
  USServo2.attach(US_SERVO_2_PIN , 500 , 2400);
  wifiServo.write(90);
  USServo1.write(90); //下面
  USServo2.write(90);
}

void loop()
{
  run();
  scan();
  
  A();
  scan2();
  A();
  
c1 = 0;
c2 = 0;
c3 = 0;
  }
  


void scan()
{
  for(int i = 0;i <= 15;i++)
  {
    USServo1.write(45+i*3);
    d = ping() / 58;       // 把高脈衝時間值換算成公分單位
      if(d < 15)
        c1++;
    delay(5); 
  }
  
  
  
  for(int i = 0;i <= 15;i++)
  {
    USServo1.write(90+i*3.5);
    d = ping() / 58;       // 把高脈衝時間值換算成公分單位
      if(d < 15)
        c3++;
    delay(5); 
  }
   
}

void scan2(){
  for(int i = 0;i <= 15;i++)
  {
    USServo1.write(142.5-i*3.5);
    d = ping() / 58;       // 把高脈衝時間值換算成公分單位
      if(d < 15)
        c3++;
    delay(5); 
  }
  
  for(int i = 0;i <= 15;i++)
  {
    USServo1.write(90-i*3);
    d = ping() / 58;       // 把高脈衝時間值換算成公分單位
      if(d < 15)
        c1++;
    delay(5); 
  }}
void A(){
  if((c1+c3) >= 10)
  {
    if(c1 >= 6 && c1 > c3)
    {brake();
    delay(50);
      right();
      delay(500);
      run();
      delay(500);
    }
    else if(c3 >= 6 && c1 < c3)
    {brake();
    delay(50);
      left();
      delay(500);
       run();
      delay(500);
    }
  }
  
    }
    
void run()
{
  digitalWrite(DIR_R1, LOW);
  analogWrite(PWM_R1, PWM_SPEED+30*0.7);
  digitalWrite(DIR_L1, LOW);
  analogWrite(PWM_L1, PWM_SPEED+20*0.7);
  digitalWrite(DIR_R2, LOW);
  analogWrite(PWM_R2, PWM_SPEED+20*0.7);
  digitalWrite(DIR_L2, LOW);
  analogWrite(PWM_L2, PWM_SPEED+20*0.7);
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
  analogWrite(PWM_R1, PWM_SPEED+50*0.7);
  digitalWrite(DIR_L1, LOW);
  analogWrite(PWM_L1, PWM_SPEED+60*0.7);
  digitalWrite(DIR_R2, LOW);
  analogWrite(PWM_R2, PWM_SPEED+70*0.7);
  digitalWrite(DIR_L2, HIGH);
  analogWrite(PWM_L2, PWM_SPEED+60*0.7);
}

void left()
{
  digitalWrite(DIR_R1, LOW);
  analogWrite(PWM_R1, PWM_SPEED+55*0.7);
  digitalWrite(DIR_L1, HIGH);
  analogWrite(PWM_L1, PWM_SPEED+65*0.7);
  digitalWrite(DIR_R2, HIGH);
  analogWrite(PWM_R2, PWM_SPEED+60*0.7);
  digitalWrite(DIR_L2, LOW);
  analogWrite(PWM_L2, PWM_SPEED+55*0.7);
}

void spin_right()
{
  digitalWrite(DIR_R1, HIGH);
  analogWrite(PWM_R1, PWM_SPEED);
  digitalWrite(DIR_L1, LOW);
  analogWrite(PWM_L1, PWM_SPEED);
  digitalWrite(DIR_R2, HIGH);
  analogWrite(PWM_R2, PWM_SPEED);
  digitalWrite(DIR_L2, LOW);
  analogWrite(PWM_L2, PWM_SPEED);
}

void spin_left()
{
  digitalWrite(DIR_R1, LOW);
  analogWrite(PWM_R1, PWM_SPEED);
  digitalWrite(DIR_L1, HIGH);
  analogWrite(PWM_L1, PWM_SPEED);
  digitalWrite(DIR_R2, LOW);
  analogWrite(PWM_R2, PWM_SPEED);
  digitalWrite(DIR_L2, HIGH);
  analogWrite(PWM_L2, PWM_SPEED);
}

void back()
{

  digitalWrite(DIR_R1, HIGH);
  analogWrite(PWM_R1, PWM_SPEED);
  digitalWrite(DIR_L1, HIGH);
  analogWrite(PWM_L1, PWM_SPEED);
  digitalWrite(DIR_R2, HIGH);
  analogWrite(PWM_R2, PWM_SPEED);
  digitalWrite(DIR_L2, HIGH);
  analogWrite(PWM_L2, PWM_SPEED);
}

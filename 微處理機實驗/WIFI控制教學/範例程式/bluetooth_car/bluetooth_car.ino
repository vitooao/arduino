#include <SoftwareSerial.h>   // 引用程式庫
 
// 定義連接藍牙模組的序列埠
SoftwareSerial BT(12, 13); // 接收腳, 傳送腳   藍芽模組(TX, RX)
char val;  // 儲存接收資料的變數

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

int PWM_SPEED = 100;

void setup() {
  pinMode(PWM_R1, OUTPUT);
  pinMode(PWM_L1, OUTPUT);
  pinMode(PWM_R2, OUTPUT);
  pinMode(PWM_L2, OUTPUT);
  pinMode(DIR_R1, OUTPUT);
  pinMode(DIR_L1, OUTPUT);
  pinMode(DIR_R2, OUTPUT);
  pinMode(DIR_L2, OUTPUT);
  
  Serial.begin(9600);   // 與電腦序列埠連線
  Serial.println("BT is ready!");
 
  // 設定HC-05藍牙模組，AT命令模式的連線速率。
  BT.begin(38400);  //HC-06預設值為9600
}
 
void loop() {
 
  // 若收到藍牙模組的資料，則判斷行走方向
  if (BT.available()) {
    val = BT.read();
    Serial.println(val);
      switch(val) {
        case 'w': //向前
          run();
          break;
        case 'a': //左轉
          spin_left();
          break;
        case 's': //向後
          back();
          break;
        case 'd': //右轉
          spin_right();
          break;
        case 'f': //停止(正方形按鈕)
          brake();
          break;
        default:  //非以上都停止
          brake();
          break;
    }
  }
}

void run()
{
  digitalWrite(DIR_R1, LOW);
  analogWrite(PWM_R1, PWM_SPEED);
  digitalWrite(DIR_L1, LOW);
  analogWrite(PWM_L1, PWM_SPEED);
  digitalWrite(DIR_R2, LOW);
  analogWrite(PWM_R2, PWM_SPEED);
  digitalWrite(DIR_L2, LOW);
  analogWrite(PWM_L2, PWM_SPEED);
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

void left()
{
  digitalWrite(DIR_R1, HIGH);
  analogWrite(PWM_R1, PWM_SPEED);
  digitalWrite(DIR_L1, LOW);
  analogWrite(PWM_L1, PWM_SPEED);
  digitalWrite(DIR_R2, LOW);
  analogWrite(PWM_R2, PWM_SPEED);
  digitalWrite(DIR_L2, HIGH);
  analogWrite(PWM_L2, PWM_SPEED);
}

void right()
{
  digitalWrite(DIR_R1, LOW);
  analogWrite(PWM_R1, PWM_SPEED);
  digitalWrite(DIR_L1, HIGH);
  analogWrite(PWM_L1, PWM_SPEED);
  digitalWrite(DIR_R2, HIGH);
  analogWrite(PWM_R2, PWM_SPEED);
  digitalWrite(DIR_L2, LOW);
  analogWrite(PWM_L2, PWM_SPEED);
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

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

  Serial.begin(9600);
  Serial.println("Ready");

  wifiServo.attach(WIFI_SERVO_PIN , 500 , 2400);
  USServo1.attach(US_SERVO_1_PIN , 500 , 2400);
  USServo2.attach(US_SERVO_2_PIN , 500 , 2400);
  wifiServo.write(90);
  USServo1.write(90);
  USServo2.write(90);
}

void loop()
{
  run();
  delay(700);
  left();
  delay(700);
  right();
  delay(700);
  back();
  delay(700);
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

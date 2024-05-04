//
//  馬達腳位定義
//
const int PWM_R1 = 11;  // 右前輪速度控制腳位
const int PWM_L1 = 6;   // 左前輪速度控制腳位
const int PWM_R2 = 5;   // 右後輪速度控制腳位
const int PWM_L2 = 3;   // 左後輪速度控制腳位

const int DIR_R1 = 8;   // 右前輪旋轉方向控制腳位
const int DIR_L1 = 7;   // 右前輪旋轉方向控制腳位
const int DIR_R2 = 4;   // 右前輪旋轉方向控制腳位
const int DIR_L2 = 2;   // 右前輪旋轉方向控制腳位

int PWM_SPEED = 100;    // 速度值 (0 ~ 255)

void setup() {
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
}

void loop() {
  if (Serial.available()>0)
  {
    char data = Serial.read();
    Serial.print("> ");
    Serial.println(data);
    
    switch (data)
    {
      case 'w':
        Serial.println("forward");
        run();
        break;
      case 's':
        Serial.println("backward");
        back();
        break;
      case 'a':
        Serial.println("left");
        left();
        break;
      case 'd':
        Serial.println("right");
        right();
        break;
      case 'q':
        Serial.println("turn left");
        spin_left();
        break;
      case 'e':
        Serial.println("turn right");
        spin_right();
        break;
      case 'b':
        Serial.println("brake");
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



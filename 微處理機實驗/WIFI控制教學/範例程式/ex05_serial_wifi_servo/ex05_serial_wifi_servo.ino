//
// Title       : 範例三
// Description : 使用 Arduino 接收攝像頭模組資料並回傳
//
#include <Servo.h>

Servo wifiServo;
int wifiServoValue;
#define WIFI_SERVO_PIN 17

//
// Serial
//
String Serial_inputString = "";    // Serial 輸入字串
const int Serial_inputLength = 30; // Serial 接收保留長度
bool Serial_startFlag = false;     // Serial 開始接收旗標
bool Serial_newLine = false;       // Serial 新資料旗標

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
  Serial_inputString.reserve(Serial_inputLength); // 預先保留字串長度

  wifiServo.attach(WIFI_SERVO_PIN , 500 , 2400);
}

void loop()
{
  Serial_read();      // Serial 讀取資料
  Serial_dataParse(); // Serial 字串資料處理
}

//
// 處理 Serial 接收
//
void Serial_read()
{
  while (Serial.available() && !Serial_newLine)
  {

    //一個字節一個字節地讀,下一句是讀到的放入字符串數組中組成一個完成的數據包
    char IncomingByte = Serial.read();
    if (IncomingByte == '\0')
      continue;
    if (IncomingByte == '$') // 當接收到 開頭字元
    {
      // 錯誤情況，當接收到二次標頭，清除
      if (Serial_startFlag)
        Serial_inputString = "";
      Serial_startFlag = true; // 開始組合資料
    }
    if (Serial_startFlag == true)
      Serial_inputString += (char)IncomingByte; // 將字元一個個串接
    if (IncomingByte == '#')                    // 當接收到結尾字元
    {
      Serial_startFlag = false; // 結束接收串接程序
      Serial_newLine = true;    // 標記為資料接收完成 (完整字串)
    }
  }
}

//
// 資料解析
//
void Serial_dataParse()
{
  if (!Serial_newLine) // 如果沒有新資料
    return;            // 結束此資料解析
  Serial.print(">> ");
  Serial.println(Serial_inputString);

  // 解析完成，清除
  Serial_newLine = false;
  Serial_inputString = "";
}

void servoCommand_dataParse()
{
  char mode = Serial_inputString[7]; // 判斷是方向還是角度指令

  if (mode == 'U')                   // UD 設定舵機角度
  {
    // 將字元轉成數字
    int hundreds = (Serial_inputString[9] - '0') * 100;
    int tens = (Serial_inputString[10] - '0') * 10;
    int units = (Serial_inputString[11] - '0');
    wifiServoValue = hundreds + tens + units;
    
  }
  else // LR 左右旋轉
  {
    char action = Serial_inputString[9];
    switch (action)
    {
    case 'L':
      wifiServoValue -= 10;
      break;

    case 'R':
      wifiServoValue += 10;
      
      break;

    default:
      break;
    }
  }

  // 限制角度
  if (wifiServoValue < 0)
    wifiServoValue = 0;
  else if (wifiServoValue > 180)
    wifiServoValue = 180;

  wifiServo.write(wifiServoValue);
  Serial.print("Servo = ");
  Serial.println(wifiServoValue);
}

//
// WIFI 模組解析
//
void generalCommand_dataParse()
{
  //小車原地左旋右旋判斷
  int direction = Serial_inputString[1] - '0';
  int speedCtrl = Serial_inputString[3] - '0';
  int beep = Serial_inputString[5] - '0';
  int light = Serial_inputString[7] - '0';

  setDirection(direction);  // 方向控制

  //速度控制
  switch (speedCtrl)
  {
  case 0:
    break;
  case 1:
    PWM_SPEED += 10;
    if (PWM_SPEED > 255)
      PWM_SPEED = 255;
    break;
  case 2:
    PWM_SPEED -= 10;
    if (PWM_SPEED < 10)
      PWM_SPEED = 10;
    break;
  }
  Serial.println(PWM_SPEED);
}

//
// 馬達控制
//
void setDirection(int direction)
{
  //方向控制
  switch (direction)
  {
  case 0:
    Serial.println("brake");
    brake();
    break;
  case 1:
    Serial.println("run");
    run();
    break;
  case 2:
    Serial.println("back");
    back();
    break;
  case 3:
    Serial.println("left");
    left();
    break;
  case 4:
    Serial.println("right");
    right();
    break;
  case 5:
    Serial.println("turn left");
    spin_left();
    break;
  case 6:
    Serial.println("turn right");
    spin_right();
    break;
  case 7:
    Serial.println("brake");
    brake();
    break;
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

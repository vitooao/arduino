#define SensorLeft  A0   //紅外線感測器左邊腳位
#define SensorC     A1  //紅外線感測器中間腳位
#define SensorRight A2  //紅外線感測器右邊腳位

int SL;                 //紅外線感測器左邊的值
int SR;                 //紅外線感測器右邊的值
int SC;                 //紅外線感測器中間的值

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

int PWM_SPEED =80;

void forward()            ///宣告直走副程式
{
  digitalWrite(DIR_R1, HIGH);
  analogWrite(PWM_R1, PWM_SPEED+30); //110
  digitalWrite(DIR_L1, HIGH);
  analogWrite(PWM_L1, PWM_SPEED+20); //100
  digitalWrite(DIR_R2, HIGH);
  analogWrite(PWM_R2, PWM_SPEED+20); //100
  digitalWrite(DIR_L2, HIGH);
  analogWrite(PWM_L2, PWM_SPEED+20); //100
}



void turnLeft()            ///宣告左轉副程式
{
  digitalWrite(DIR_R1, LOW);
  analogWrite(PWM_R1, 0);
  digitalWrite(DIR_L1, HIGH);
  analogWrite(PWM_L1, PWM_SPEED+80);
  digitalWrite(DIR_R2, LOW);
  analogWrite(PWM_R2, 0);
  digitalWrite(DIR_L2, HIGH);
  analogWrite(PWM_L2, PWM_SPEED+80);
}

void turnLeft_quickly()            ///宣告快速左轉副程式
{
  digitalWrite(DIR_R1, HIGH);
  analogWrite(PWM_R1, 0);
  digitalWrite(DIR_L1, LOW);
  analogWrite(PWM_L1, PWM_SPEED+60);
  digitalWrite(DIR_R2, HIGH);
  analogWrite(PWM_R2, PWM_SPEED+60);
  digitalWrite(DIR_L2, LOW);
  analogWrite(PWM_L2, PWM_SPEED+60);
}

void turnRight()            ///宣告右轉副程式
{
  digitalWrite(DIR_R1, HIGH);
  analogWrite(PWM_R1, PWM_SPEED+80);
  digitalWrite(DIR_L1, LOW);
  analogWrite(PWM_L1, 0);
  digitalWrite(DIR_R2, HIGH);
  analogWrite(PWM_R2, PWM_SPEED+80);
  digitalWrite(DIR_L2, LOW);
  analogWrite(PWM_L2, 0);
}

void turnRight_quickly()            ///宣告快速右轉副程式
{
  digitalWrite(DIR_R1, LOW);
  analogWrite(PWM_R1, PWM_SPEED+60);
  digitalWrite(DIR_L1, HIGH);
  analogWrite(PWM_L1, 0);
  digitalWrite(DIR_R2, LOW);
  analogWrite(PWM_R2, PWM_SPEED+60);
  digitalWrite(DIR_L2, HIGH);
  analogWrite(PWM_L2, PWM_SPEED+60);
}
void slow()
{

  digitalWrite(DIR_R1, LOW);
  analogWrite(PWM_R1, 77);
  digitalWrite(DIR_L1, LOW);
  analogWrite(PWM_L1, 70);
  digitalWrite(DIR_R2, LOW);
  analogWrite(PWM_R2, 70);
  digitalWrite(DIR_L2, LOW);
  analogWrite(PWM_L2, 70);
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

  Serial.begin(9600);            ///啟動通訊序阜列
  Serial.println("Ready");            ///在通訊序阜列中顯示Ready

}

void loop()
{
  SL=digitalRead(SensorLeft);            ///讀取A0的訊號
  SC=digitalRead(SensorC);               ///讀取A1的訊號        
  SR=digitalRead(SensorRight);            ///讀取A2的訊號
 
  Serial.print("sr=");            ///在通訊序阜列中表示目前右邊的感測器是否偵測訊號           
  Serial.println(SR);
  Serial.print("sl=");            ///在通訊序阜列中表示目前左邊的感測器是否偵測訊號   
  Serial.println(SL);
  Serial.print("sc=");
  Serial.println(SC);            ///在通訊序阜列中表示目前中間的感測器是否偵測訊號     
  Serial.println("");
   
 
  if (SL==LOW||SR==LOW) {
    if (SL==LOW&&SR==LOW) {
    forward();}
     if(SL==LOW){
      turnRight();
      }
     if(SR==LOW){ 
      turnLeft();                                        
      }
}
 if(SC==LOW){
     if(SL==LOW){
      turnRight_quickly();
      }
     if(SR==LOW){ 
      turnLeft_quickly();                                        
      }
  
  }
     if (SC==LOW&&SL==HIGH&&SR==HIGH)                //當左右感測器的值皆為0,向前
  {
    forward();
  }
  if (SC==HIGH&&SL==HIGH&&SR==HIGH)                
  {
    slow();
  }
  if (SC==LOW&&SL==LOW&&SR==LOW)                
  {
    forward();
  }
}

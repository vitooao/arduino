// pin 2 of 4HC595 pin (SER)
const byte dataPin  = 6;    
// pin 4 of 4HC595 pin (RCLK)
const byte latchPin = 4;   
// pin 5 of 4HC595 pin (SRCLK)
const byte clockPin = 5;  
byte x;
byte y;
const byte LED[8] =
{
  
  B00000001,  //1
  B00000010,  //2
  B00000100,  //3
  B00001000,  //4
  B00010000,  //5
  B00100000,  //6
  B01000000,  //7
  B10000000,  //8
     
};
void setup() 
{
  // Set all the pins of 74HC595 as OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(A5));
 
}
void loop() 
{
 int w=random(0,7); //設定隨機數
  A(w);             //帶入副程式
}
void A(int w)
{
  
   int x=100;
  for(int i=0;i<=2;i++){    //先轉3圈(漸慢)
    for(int y=0;y<=7;y++){
      digitalWrite(latchPin, LOW);  // 送資料前要先把 latchPin 設成低電位
      shiftOut(dataPin, clockPin, LSBFIRST, LED[w]); 
      shiftOut(dataPin, clockPin, LSBFIRST, LED[y]); 
      digitalWrite(latchPin, HIGH);
      delay(x);
      }
    x=x*2;
    }  
  for(int z=0;z<=w+4;z++){      //內圈10000000與外圈00001000最近
      digitalWrite(latchPin, LOW);  // 送資料前要先把 latchPin 設成低電位
      shiftOut(dataPin, clockPin, LSBFIRST, LED[w]); 
      shiftOut(dataPin, clockPin, LSBFIRST, LED[z]); //停在同一位置
      digitalWrite(latchPin, HIGH);
      delay(x);
      }
      delay(5000);
}

//擴充性
//副程式化
#include "pitches.h"

const byte dataPin  = 6;// pin 2 of 4HC595 pin (SER)    
const byte latchPin = 4;// pin 4 of 4HC595 pin (RCLK)
const byte clockPin = 5;// pin 5 of 4HC595 pin (SRCLK)
int Buzzer_Pin_BZ = 3; // 蜂鳴器腳位設定

const int buttonPin_S6=7; //the number of the pushbutton pin
const int buttonPin_S7=8; //the number of the pushbutton pin
const int ledPin=13; //the number of the LED pin

volatile int led_count=0;
int debounceDelay=200; //debounce delay (ms)
volatile int systemstate=0;
int LED_inner=0,LED_set=0;
int w=0;


// 開關S6的相關變數宣告
int ledState_S6=HIGH; //the current state of the output pin
int buttonState_S6; //previous stable state of the input pin
int lastButtonState_S6=LOW; //the previous reading from the input pin
long lastDebounceTime_S6=0; //the last time the output pin was toggled
long debounceDelay_S6=50; //the debounce time; increase if the output flickers

// 開關S7的相關變數宣告
int ledState_S7=HIGH; //the current state of the output pin
int buttonState_S7; //previous stable state of the input pin
int lastbuttonState_S7=LOW; //the previous reading from the input pin
long lastDebounceTime_S7=0; //the last time the output pin was toggled
long debounceDelay_S7=50; //the debounce time; increase if the output flickers





const byte LED[18] =
{
  B00000000,  //0
  B00000100,  //1
  B00000010,  //2
  B00000001,  //3
  B10000000,  //4
  B01000000,  //5
  B00100000,  //6
  B00010000,  //7
  B00001000,  //8
  B01000000,  //9
  B00100000,  //10
  B00010000,  //11
  B00001000,  //12
  B00000100,  //13
  B00000010,  //14
  B00000001,  //15
  B10000000,  //16
  B11111111,  //18   
};

int star[]={NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,
            NOTE_B4,NOTE_G4,NOTE_G4,NOTE_F4,NOTE_E4,NOTE_F4,NOTE_G4,
            NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,
            NOTE_G4,NOTE_F4,NOTE_E4,NOTE_F4,NOTE_E4,NOTE_C4,NOTE_C4,};
int beat[]={4,4,2,4,4,2,   
            4,4,4,4,4,4,2, 
            4,4,2,4,4,2,   
            4,4,4,4,4,4,2, 
};  

void music()
{
    for(int i=0; i<=25; i++)
     {
       int duration = 1100/beat[i];
       tone(Buzzer_Pin_BZ, star[i], duration);  
       int pauseBetweenNote=duration * 1.15;
       delay(pauseBetweenNote);   // 每個音間
     }
}
void led_display(int led1,int led2)
{
  //LED1 的範圍是1~8
  //LED2 的範圍是9-15
  //0是全滅，1是全亮
  digitalWrite(latchPin, LOW);  // 送資料前要先把 latchPin 設成低電位
  shiftOut(dataPin, clockPin, LSBFIRST, LED[led1]); 
  shiftOut(dataPin, clockPin, LSBFIRST, LED[led2]); 
  digitalWrite(latchPin, HIGH);
  //delay(300);
}

void int0() 
  { //interrupt handler
   if (debounced()) 
   { 
    led_count++;
      if (led_count>8)
        led_count=0;
    led_display(led_count,0);
   }
  }
  
//中斷開關防彈跳效應
boolean debounced() { //check if debounced
  static unsigned long lastMillis=0; //record last millis
  unsigned long currentMillis=millis(); //get current elapsed time
  if ((currentMillis-lastMillis) > debounceDelay) {
    lastMillis=currentMillis; //update lastMillis with currentMillis
    return true; //debounced
    }
  else {return false;} //not debounced
  }
  
//S6的防彈跳副程式    
boolean debounced_S6(int pin) { //check if debounced
  boolean debounced=false;  //default
  int reading=digitalRead(pin);  //current button state
  if (reading != lastButtonState_S6) { //button state changed
    lastDebounceTime_S6=millis(); //update last debounce time
    }
  if ((millis() - lastDebounceTime_S6) > debounceDelay_S6) { //overtime
    if (reading != buttonState_S6) { //button state has changed
      buttonState_S6=reading; //update previous stable button state
      if (buttonState_S6 == LOW) { //button pressed
        debounced=true;
        }
      }
    }
  lastButtonState_S6=reading; //update last button state
  return debounced;
  }

//S7的防彈跳副程式 
boolean debounced_S7(int pin) { //check if debounced
  boolean debounced=false;  //default
  int reading=digitalRead(pin);  //current button state
  if (reading != lastbuttonState_S7) { //button state changed
    lastDebounceTime_S7=millis(); //update last debounce time
    }
  if ((millis() - lastDebounceTime_S7) > debounceDelay_S7) { //overtime
    if (reading != buttonState_S7) { //button state has changed
      buttonState_S7=reading; //update previous stable button state
      if (buttonState_S7 == LOW) { //button pressed
        debounced=true;
        }
      }
    }
  lastbuttonState_S7=reading; //update last button state
  return debounced;
  }
void A(int w)
{
  
   int x=100;
  for(int i=0;i<=2;i++){    //先轉3圈(漸慢)
    for(int y=0;y<=8;y++){
      digitalWrite(latchPin, LOW);  // 送資料前要先把 latchPin 設成低電位
      shiftOut(dataPin, clockPin, LSBFIRST, LED[LED_inner]); 
      shiftOut(dataPin, clockPin, LSBFIRST, LED[y]); 
      digitalWrite(latchPin, HIGH);
      delay(x);
      }
    x=x*2;
    }  
  for(int z=0;z<=w+4;z++){      //內圈10000000與外圈00001000最近
      digitalWrite(latchPin, LOW);  // 送資料前要先把 latchPin 設成低電位
      shiftOut(dataPin, clockPin, LSBFIRST, LED[LED_inner]); 
      int v=z;
      if(v>8){
        v=v-8;
        }
      shiftOut(dataPin, clockPin, LSBFIRST, LED[v]); //停在同一位置
      digitalWrite(latchPin, HIGH);
      delay(x);
      }
      delay(3000);
}
void B(){
  for(int i=1;i<256;i=i*2){
  digitalWrite(latchPin, LOW);  // 送資料前要先把 latchPin 設成低電位
  shiftOut(dataPin, clockPin, LSBFIRST,i);    //內圈跑馬燈
  shiftOut(dataPin, clockPin, LSBFIRST,0);    //外圈不亮
  digitalWrite(latchPin, HIGH); // 送完資料後要把 latchPin 設成高電位
  delay(300);
  }
  for(int j=16;j<256;j=j*2){          //內圈10000000(128)與外圈00001000(16)最近
  digitalWrite(latchPin, LOW);  
  shiftOut(dataPin, clockPin, LSBFIRST,0);    //內圈不亮
  shiftOut(dataPin, clockPin, LSBFIRST,j);    //外圈跑馬燈
  digitalWrite(latchPin, HIGH); 
  delay(300);
 }
 for(int k=1;k<9;k=k*2){              
  digitalWrite(latchPin, LOW);          
  shiftOut(dataPin, clockPin, LSBFIRST,0);    //內圈不亮
  shiftOut(dataPin, clockPin, LSBFIRST,k);    //外圈跑馬燈
  digitalWrite(latchPin, HIGH); 
  delay(300);
 }}
void setup() 
{
  // initialize serial:
  Serial.begin(9600);
  // Set all the pins of 74HC595 as OUTPUT
  randomSeed(analogRead(A0));
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  //Buzzer
  pinMode(Buzzer_Pin_BZ,OUTPUT);
  //S6
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin_S6, INPUT); //enable pullup resistor
  pinMode(buttonPin_S7, INPUT); //enable pullup resistor
  digitalWrite(ledPin, ledState_S6);
  //中斷
  attachInterrupt(0, int0, RISING); //assign int0
  systemstate=1;
  
}



void loop() 
{
     
      /*int i;
      i=random(1,16);
      if(i<=8)
      led_display(i,0);
      if(i>8)
      led_display(0,i);*/
      //music();
      //led_display(led_count,0);
      
       switch (systemstate) 
       {
         case 1:
                led_display(0,0);
                music();
                systemstate=2;
                break;
         case 2:
                  
                 if (debounced_S6(buttonPin_S6)) 
                    { //debounced 執行的動作
                      LED_inner++;   
                      if (LED_inner>8)
                        LED_inner=1;                   
                    }
                 if (debounced_S7(buttonPin_S7)) 
                    { //debounced 執行的動作
                      LED_set=LED_inner; //LED_set 玩家選的led
                      
                      // 是非常*10000重要 的技巧
                      Serial.print("LED_inner=");
                      Serial.println(LED_inner);
                      Serial.print("LED_set=");
                      Serial.println(LED_set);
                      
                      
                      led_display(LED_set,0);
                      delay(200); 
                      led_display(0,0);
                      delay(200);                       
                      led_display(LED_set,0);
                      delay(200);                       
                      led_display(0,0);
                      delay(200); 
                      systemstate=3; //2的流程已經完成                                                                
                    }
                 //設定內圈的上下限   
                 led_display(LED_inner,0);                
                 break;
         case 3:
                 w=8;
                 Serial.println(w);
                 A(w);
                 systemstate=4; //上周的回家作業
                 break; 
         case 4:
                if(w==LED_set){
                  B();
                  }
                else{
                    if(w+4>8){
                      w=w-8;}
                      led_display(LED_set,w+4);
                      delay(500); 
                      led_display(0,0);
                      delay(200);                       
                      led_display(LED_set,w+4);
                      delay(500);                       
                      led_display(0,0);
                      delay(200); 
                      led_display(LED_set,w+4);
                      delay(500);
                      led_display(0,0);
                  }
                systemstate=5; //3的流程已經完成
                break; 
         case 5:
                //判斷是否相等的介面顯示
                systemstate=1; //重新執行遊戲
                break;        
         default:
                break;
       }         
}

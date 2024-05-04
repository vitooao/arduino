#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int hour1=0;
int hour2=0;
int min1=0;
int min2=0;
int sec1=0;
int sec2=0;
int x=0;
int y=0;    
int i;int j;int k;int m;
int s=59;
int lcd_key = 0;
int adc_key_in = 0;
#define btnRIGHT 0
#define btnUP 1
#define btnDOWN 2
#define btnLEFT 3
#define btnSELECT 4
#define btnNONE 5
int read_LCD_buttons()
{
adc_key_in = analogRead(0); 

if (adc_key_in < 50) return btnRIGHT;
if (adc_key_in < 195) return btnUP;
if (adc_key_in < 380) return btnDOWN;
if (adc_key_in < 555) return btnLEFT;
if (adc_key_in < 790) return btnSELECT;

return btnNONE; // when all others fail, return this...
}
void A(){
      for(sec1;sec1>=0;sec1--){
        for(sec2;sec2>=0;sec2--){
        lcd.setCursor(7,0);
        lcd.print(sec2);
        delay(1);
            }
       lcd.setCursor(6,0);
       i=sec1;
       if(i<1){i=1;}
       lcd.print(i-1);
       sec2=9;
            }
       sec1=0;
       sec2=0;
       //先把秒的部分數完
                   
      for(min1;min1>=0;min1--){
        for(min2;min2>0;min2--){
         lcd.setCursor(4,0);
        k=min2;
       if(k<1){k=1;}
       lcd.print(k-1);
        s=59;
          for(s;s>=10;s--){
           lcd.setCursor(6,0);
           lcd.print(s);
           delay(1);
           }
           lcd.setCursor(6,0);
           lcd.print(0);
           for(s;s>=0;s--){
           lcd.setCursor(7,0);
           lcd.print(s);
           delay(1);
           }
            }
       lcd.setCursor(3,0);
      j=min1;
       if(j<1){j=1;}
       lcd.print(j-1);
       Serial.print(min1);
           Serial.print(" ");
           Serial.print(min2);
           Serial.print(" ");
           Serial.println(j);
       min2=10;
            }
        //把分鐘部分數完(分鐘每減一，秒數部分就從60減到零)
       
       min1=0;
       min2=0;
       
      for(hour1;hour1>=0;hour1--){
        for(hour2;hour2>0;hour2--){
         lcd.setCursor(1,0);
        k=hour2;
       if(k<1){k=1;}
       lcd.print(k-1);
       m=59;
       for(m;m>=10;m--){
       lcd.setCursor(3,0);
       lcd.print(m);
        s=59;
          for(s;s>=10;s--){
           lcd.setCursor(6,0);
           lcd.print(s);
           delay(1);
           }
           lcd.setCursor(6,0);
           lcd.print(0);
           for(s;s>=0;s--){
           lcd.setCursor(7,0);
           lcd.print(s);
           delay(1);
           }
            }
            lcd.setCursor(3,0);
           lcd.print(0);
       for(m;m>=0;m--){
       lcd.setCursor(4,0);
       lcd.print(m);
        s=59;
          for(s;s>=10;s--){
           lcd.setCursor(6,0);
           lcd.print(s);
           delay(1);
           }
           lcd.setCursor(6,0);
           lcd.print(0);
           for(s;s>=0;s--){
           lcd.setCursor(7,0);
           lcd.print(s);
           delay(1);
           }
            }
            }
       lcd.setCursor(0,0);
      j=hour1;
       if(j<1){j=1;}
       lcd.print(j-1);
       Serial.print(hour1);
           Serial.print(" ");
           Serial.print(hour2);
           Serial.print(" ");
           Serial.println(j);
       hour2=10;
            }
       //小時數倒數。(小時減一，分鐘從60到0)(分鐘減一，秒數從60到0)
            hour1=0;
            hour2=0;
  }
void setup() {
 lcd.begin(16, 2); // start the library
lcd.setCursor(0,1);
Serial.begin(9600);
lcd.print("Setting time!");
}

void loop() {
lcd.setCursor(0,0);
lcd.print(hour1);
lcd.print(hour2);
lcd.print(":");
lcd.print(min1);
lcd.print(min2);
lcd.print(":");
lcd.print(sec1);
lcd.print(sec2); //顯示倒數時間

lcd.setCursor(x,0);
 y=x;
lcd_key = read_LCD_buttons();
switch (lcd_key) 
  {
    case btnRIGHT:        //座標設x為方向鍵所指定的座標，y為底線的座標 因為(0,3)和(0,5)是冒號，所以我一時想不到好方法就暴力破解了
    { lcd.clear();    
      delay(500);      
      x=x+1;            
      if(x>5){x=5;}
     y=x;
      if(x==2){y=3;}
      if(x==3){y=4;}
      if(x==4){y=6;}
      if(x==5){y=7;}
      lcd.setCursor(y,1);
      lcd.print("-");
      break;
        }
    case btnLEFT:
    { lcd.clear();
      delay(500);
      x=x-1;           
      if(x<0){x=0;}
      y=x;
      if(x==2){y=3;}
      if(x==3){y=4;}
      if(x==4){y=6;}
      if(x==5){y=7;}
      lcd.setCursor(y,1);
      lcd.print("-");
      break;
        }
    case btnUP:
    {     
      delay(500);
      if(x==0){hour1++;}      //
        if(hour1>9){hour1=0;}
      if(x==1){hour2++;}
        if(hour2>9){hour2=0;}
      if(x==2){min1++;}
        if(min1>6){min1=0;}
      if(x==3){min2++;}
        if(min2>9){min2=0;}
      if(x==4){sec1++;}
        if(sec1>6){sec1=0;}
      if(x==5){sec2++;}
        if(sec2>9){sec2=0;}
      break;
        }
    case btnDOWN:
    {
      delay(500);
      if(x==0){hour1--;}
        if(hour1<0){hour1=9;}
      if(x==1){hour2--;}
        if(hour2<0){hour2=9;}
      if(x==2){min1--;}
        if(min1<0){min1=6;}
      if(x==3){min2--;}
        if(min2<0){min2=9;}
      if(x==4){sec1--;}
        if(sec1<0){sec1=6;}
      if(x==5){sec2--;}
        if(sec2<0){sec2=9;}
      break;
        }
    case btnSELECT:    
    {A();//倒數的副程式
    break;
    }
    case btnNONE:      
    {
    break;
  }
}
/*Serial.print(x);
Serial.print("  ");
Serial.println(y)*/;}

#include "HCSR05.h"
#include <LiquidCrystal.h>
//使用到的PIN腳
const int pin_RS = 8; 
const int pin_EN = 9; 
const int pin_D4 = 4; 
const int pin_D5 = 5; 
const int pin_D6 = 6; 
const int pin_D7 = 7; 
//填入正確的PIN腳，建立LCD物件
LiquidCrystal lcd( pin_RS,  pin_EN,  pin_D4,  pin_D5,  pin_D6,  pin_D7);
HCSR05 sr05(13,12);
float distance;
void setup() {
 Serial.begin(9600);
lcd.begin(16, 2);
}

void loop() {
 distance=sr05.ping();
 Serial.print(distance);
 Serial.println( "cm" );
 lcd.setCursor(0,0);
   lcd.print("Distance");
   lcd.setCursor(14,0);
   lcd.print("cm");
   lcd.setCursor(9,0);
   lcd.print(distance,1);
 delay(1000);
 lcd.clear();
}

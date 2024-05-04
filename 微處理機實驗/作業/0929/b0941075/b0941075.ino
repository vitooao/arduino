#include <LiquidCrystal.h>
#include <Keypad.h>    // 引用Keypad程式庫
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

#define KEY_ROWS 4 // 按鍵模組的列數
#define KEY_COLS 4 // 按鍵模組的行數
int x=0;
// 依照行、列排列的按鍵字元（二維陣列）
char keymap[KEY_ROWS][KEY_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte colPins[KEY_COLS] = {19, 18, 17, 16};     // 按鍵模組，行1~4接腳。
byte rowPins[KEY_ROWS] = {13, 12, 11, 10}; // 按鍵模組，列1~4接腳。 
// 初始化Keypad物件
// 語法：Keypad(makeKeymap(按鍵字元的二維陣列), 模組列接腳, 模組行接腳, 模組列數, 模組行數)
Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, KEY_ROWS, KEY_COLS);
char password[4]={'7','4','1','4'}; //密碼 
char inputCode[4]={'0','0','0','0'};//輸入的4位數

void setup() {
  lcd.begin(16, 2);
   Serial.begin(9600);
   lcd.setCursor(0,0);
   lcd.print("Password,please"); 
   lcd.setCursor(0,1);
   lcd.print("PIN:");
   lcd.setCursor(4,1);
}

void loop() {
  // 透過Keypad物件的getKey()方法讀取按鍵的字元

  char key = myKeypad.getKey();
  if (key){  // 若有按鍵被按下…
    Serial.println(key);// 顯示按鍵的字元
    delay(500);
    lcd.print("*");
    inputCode[x]= key;
     x++;
     Serial.println(password);
     Serial.println(inputCode);
  }
  if(x==4){
    x=0;
    delay(1500);
    if(password[0]==inputCode[0]&&password[1]==inputCode[1]&&password[2]==inputCode[2]&&password[3]==inputCode[3]){//判定密碼是否輸入正確
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Hello");
      lcd.setCursor(0,1);
      lcd.print("Good to see you");
      delay(3000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Password,please");
      lcd.setCursor(0,1);
      lcd.print("PIN:");
      char inputCode[4]={'0','0','0','0'};
    }else{
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("PIN");
      lcd.setCursor(0,1);
      lcd.print("wrong!");
      delay(3000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Password,please");
      lcd.setCursor(0,1);
      lcd.print("PIN:");
      char inputCode[4]={'0','0','0','0'};
      }
  }
  
  
  }

#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int x=0,y=0;    //設變數x,改變小精靈位置
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

byte sp[6][8] = {
  {B00100, B01110, B11111, B10101, B11111, B01110, B01010, B10001},
  {B00100, B01110, B11111, B11010, B11111, B00100, B01010, B01010},
  {B00100, B01110, B11111, B11110, B11111, B01110, B00100, B00100},
  {B00100, B01110, B11111, B11111, B11111, B00100, B01010, B01010},
  {B00100, B01110, B11111, B01111, B11111, B01110, B00100, B00100},
  {B00100, B01110, B11111, B01101, B11111, B00100, B01010, B01010}
};//小精靈圖案

byte index = 0;
void setup()
{
lcd.begin(16, 2); // start the library
lcd.setCursor(0,0);
Serial.begin(9600);
for (byte i=0; i<6; i++) {
    lcd.createChar (i, sp[i]);
  }
}

void loop()
{
lcd.setCursor(x,y);
lcd_key = read_LCD_buttons();
lcd.write(index);  
lcd.print("hello, world!");

switch (lcd_key) // depending on which button was pushed, we perform an action
  {
    case btnRIGHT:
    {
      lcd.clear();     //清除上一個小精靈
      delay(500);      //如果不加這行直接運行下面那行的話，按鈕一按x和y的值會爆衝
      x=x+1;           //向右移動一格
      index=index+1;   //改變小精靈圖樣
      break;
        }
    case btnLEFT:
    {
      lcd.clear();
      delay(500);
      x=x-1;           //向左移動一格
      index=index+1;
      break;
        }
    case btnUP:
    {
      lcd.clear();
      delay(500);
      y=y+1;           //向上移動一格
      index=index+1;
      break;
        }
    case btnDOWN:
    {
      lcd.clear();
      delay(500);
      y=y-1;           //向下移動一格
      index=index+1;
      break;
        }
    case btnSELECT:    //沒用到，但我想留著
    {
    break;
    }
    case btnNONE:      //沒用到，但我想留著
    {
    break;
    }
  }
if (index > 5) {   // 將 index 值限制在 0~5 之間
    index = 0;
    }
if (x>15){
    x=0;
    }         //如果小精靈在最右邊時按right，小精靈會到最左邊
if (x<0){
    x=15;
    }         //如果小精靈在最左邊時按left，小精靈會到最右邊
if (y>1){
    y=0;
    }         //如果小精靈在最下面時按up，小精靈會到最上面
 if (y<0){
    y=1;
    }         //如果小精靈在最上面時按down，小精靈會到最下面
Serial.print(x);
Serial.print("  ");
Serial.print(y);
Serial.print("  ");
Serial.println(index);
}

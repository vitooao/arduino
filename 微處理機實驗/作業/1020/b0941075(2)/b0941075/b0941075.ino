#include <SPI.h>  // 引用 SPI 程式庫
// 定義 MAX7219 暫存器
const byte NOOP = 0x0;        // 不運作
const byte DECODEMODE = 0x9;  // 解碼模式
const byte INTENSITY = 0xA;   // 顯示強度
const byte SCANLIMIT = 0xB;   // 掃描限制
const byte SHUTDOWN = 0xC;    // 停機
const byte DISPLAYTEST = 0xF; // 顯示器檢測

// digit pattern for a 7-segment display. datasheet table 5
const byte B[11] =
{
  B11111010,  //0
  B01010000,  //1
  B11101001,  //2
  B11110001,  //3
  B01010011,  //4
  B10110011,  //5
  B10111011,  //6
  B01110000,  //7
  B11111011,  //8
  B11110011,  //9
  B00000000,  // all LOW
};

// 設定 MAX7219 暫存器資料的自訂函數
void max7219(byte reg, byte data) {
  digitalWrite (SS, LOW);
  SPI.transfer (reg);
  SPI.transfer (data);
  digitalWrite (SS, HIGH);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(SS, OUTPUT);     // 將預設的 SS 腳（數位 10）設成「輸出」
  digitalWrite(SS, HIGH);  // 先在 SS 腳輸出高電位
  //（代表「尚不選取周邊」）
  SPI.begin ();     // 啟動 SPI 連線
  
  max7219 (SCANLIMIT, 3);  // 設定掃描 4 行
  max7219 (DECODEMODE, 0); // 不使用 BCD 解碼
  max7219 (INTENSITY, 6);  // 設定成中等亮度
  max7219 (DISPLAYTEST, 0);// 關閉顯示器測試
  max7219 (SHUTDOWN, 1);   // 關閉停機模式（亦即，「開機」）

  // 清除顯示畫面（4顆七段設定成 0）
    for (byte i=0; i < 4; i++) {
    max7219 (i+1, B[10]);
    delay(100);
  }
  for( byte j=0; j<10;j++){
     max7219 (2, B[j]);
  for (byte i=0; i < 10; i++) {
    max7219 (1, B[i]);
    delay(100);
  }}
  //display(num);  // 七段歸零
}

void loop() {
  // put your main code here, to run repeatedly:

}

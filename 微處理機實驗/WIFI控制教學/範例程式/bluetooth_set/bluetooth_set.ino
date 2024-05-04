#include <SoftwareSerial.h>   // 引用程式庫
 
// 定義連接藍牙模組的序列埠
SoftwareSerial BT(10, 11); // 接收腳, 傳送腳   藍芽模組(TX, RX)
char val;  // 儲存接收資料的變數
 
void setup() {
  Serial.begin(9600);   // 與電腦序列埠連線
  Serial.println("BT is ready!");
 
  // 設定HC-05藍牙模組，AT命令模式的連線速率。
  BT.begin(38400);  //HC-06預設值為9600
}
 
void loop() {
  // 若收到「序列埠監控視窗」的資料，則送到藍牙模組
  if (Serial.available()) {
    val = Serial.read();
    BT.print(val);
  }
 
  // 若收到藍牙模組的資料，則送到「序列埠監控視窗」
  if (BT.available()) {
    val = BT.read();
    Serial.print(val);
  }
}

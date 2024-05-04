//
// Title       : 範例三
// Description : 使用 Arduino 接收攝像頭模組資料並回傳
//

//
// Serial
//
String Serial_inputString = "";    // Serial 輸入字串
const int Serial_inputLength = 30; // Serial 接收保留長度
bool Serial_startFlag = false;     // Serial 開始接收旗標
bool Serial_newLine = false;       // Serial 新資料旗標

void setup()
{
  Serial.begin(9600);
  Serial.println("Ready");
  Serial_inputString.reserve(Serial_inputLength); // 預先保留字串長度
}

void loop()
{
  Serial_read();
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

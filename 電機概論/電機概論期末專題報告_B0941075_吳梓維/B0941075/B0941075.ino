
int  vrx;
int  vry;
int  sw;
int  col;
int  row;
int x1;
int x2;
int x3;
int y1;
int y2;
int y3;

int Max7219_pinCLK_11= 11;
int Max7219_pinDIN_12= 12;
int Max7219_pinCS_10= 10;

const byte LED1=8; int check1;
const byte LED2=9; int check2;
const byte LED3=13;int check3;//三個綠色LED 表示完成進度

const byte LEDa=3; 
const byte LEDb=4; 
const byte LEDc=5; 
const byte LEDd=6; 
const byte LEDe=7; //四個黃色LED 一個紅色LED 表示挑戰次數
int count;       //設定參數

void Write_Max7219_byte_11_12_10(unsigned char DATA){
     unsigned char i;
     digitalWrite(Max7219_pinCS_10,LOW);
     for(i=8;i>=1;i--)
     {
         digitalWrite(Max7219_pinCLK_11,LOW);
         digitalWrite(Max7219_pinDIN_12,DATA&0x80);
         DATA = DATA<<1;
         digitalWrite(Max7219_pinCLK_11,HIGH);
      }
}

void Write_Max7219_11_12_10(unsigned char address,unsigned char dat){
      digitalWrite(Max7219_pinCS_10,LOW);
      Write_Max7219_byte_11_12_10(address);
      Write_Max7219_byte_11_12_10(dat);
      digitalWrite(Max7219_pinCS_10,HIGH);
}

void Init_MAX7219_11_12_10(void) {
      Write_Max7219_11_12_10(0x09, 0x00);
      Write_Max7219_11_12_10(0x0a, 0x03);
      Write_Max7219_11_12_10(0x0b, 0x07);
      Write_Max7219_11_12_10(0x0c, 0x01);
      Write_Max7219_11_12_10(0x0f, 0x00);
}

void Display_MAX721911_12_10(unsigned char dat[]) {
      for(int i=1; i < 9; i++)
          Write_Max7219_11_12_10(i, dat[i-1]);
}

unsigned char MAX7219_displaybuffer_11_12_10[9]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,};

unsigned char MAX7219_disp_11_12_10_circle1[9]={0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,}; //圈圈動畫
unsigned char MAX7219_disp_11_12_10_circle2[9]={0x00,0x00,0x3c,0x24,0x24,0x3c,0x00,0x00,};
unsigned char MAX7219_disp_11_12_10_circle3[9]={0x00,0x7e,0x42,0x42,0x42,0x42,0x7e,0x00,};
unsigned char MAX7219_disp_11_12_10_circle4[9]={0xff,0x81,0x81,0x81,0x81,0x81,0x81,0xff,};

unsigned char MAX7219_disp_11_12_10_fork1[9]={0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,};   //叉叉動畫
unsigned char MAX7219_disp_11_12_10_fork2[9]={0x00,0x00,0x24,0x18,0x18,0x24,0x00,0x00,};
unsigned char MAX7219_disp_11_12_10_fork3[9]={0x00,0x42,0x24,0x18,0x18,0x24,0x42,0x00,};
unsigned char MAX7219_disp_11_12_10_fork4[9]={0x81,0x42,0x24,0x18,0x18,0x24,0x42,0x81,};

unsigned char MAX7219_disp_11_12_10_lough[9]={0x04,0x62,0xc4,0x80,0x80,0xc4,0x62,0x04,};    //笑臉動畫
unsigned char MAX7219_disp_11_12_10_cry[9]={0x0a,0xc4,0x6a,0x20,0x20,0x6a,0xc4,0x0a,};      //哭臉動畫

unsigned char MAX7219_disp_11_12_10_you[9]={0x03,0x0c,0x03,0x1c,0x14,0xfc,0x80,0xe0,};
unsigned char MAX7219_disp_11_12_10_win[9]={0x03,0x04,0x53,0x74,0x53,0xe0,0x20,0xe0,};
unsigned char MAX7219_disp_11_12_10_lose[9]={0x17,0xac,0xac,0x40,0x07,0xfd,0xaf,0xa8,};

void MAX7219_xy_draw11_12_10(int row, int column, int led_status) {
     if((row > 8) || (column > 8))
         return;
     if (led_status)
        MAX7219_displaybuffer_11_12_10[row-1] |= 1 << (8-column);
     else
        MAX7219_displaybuffer_11_12_10[row-1] &= ~(1 << (8-column));
     Display_MAX721911_12_10(MAX7219_displaybuffer_11_12_10);
 }

void setup()
{ randomSeed(analogRead(A0));
  x1 = random(1,9);
  y1 = random(1,9);
  x2 = random(1,9);
  y2 = random(1,9);
  x3 = random(1,9);
  y3 = random(1,9);   //隨機生成三個地雷
  pinMode(2,INPUT_PULLUP);
  Serial.begin(9600);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(Max7219_pinCLK_11,OUTPUT);
  pinMode(Max7219_pinCS_10,OUTPUT);
  pinMode(Max7219_pinDIN_12,OUTPUT);
  pinMode(LED1,OUTPUT); 
  pinMode(LED2,OUTPUT); 
  pinMode(LED3,OUTPUT); //三個綠色LED 表示完成進度
  delay(50);
  Init_MAX7219_11_12_10();
  vrx = 0;
  vry = 0;
  col = 1;
  row = 1;
}


void loop()
{
    vrx = analogRead(A4);
    vry = analogRead(A5);
    sw = digitalRead(2); 
    Serial.print(x1);
    Serial.print(y1);
    Serial.print(x2);
    Serial.print(y2);
    Serial.print(x3);
    Serial.print(y3);Serial.print(" ");//用來偷看地雷在哪個位置
    Serial.print(row);Serial.print(",");
    Serial.print(col);Serial.print("   ");
    Serial.print(vrx);Serial.print(" ;  ");
    Serial.print(vry);
    Serial.print("  SW=");
    Serial.print(sw);
    Serial.print("count=");
    Serial.println(count);
    if (vrx <= 450) {
      MAX7219_xy_draw11_12_10(row,col,0);
      row = row + 1;
      if (row > 8) {
        row = 8;
      }
    }
    if (vrx >= 550) {
      MAX7219_xy_draw11_12_10(row,col,0);
      row = row - 1;
      if (row < 1) {
        row = 1;
      }
    }
    if (vry >= 550) {
      MAX7219_xy_draw11_12_10(row,col,0);
      col = col + 1;
      if (col > 8) {
        col = 8;
      }
    }
    if (vry <= 450) {
      MAX7219_xy_draw11_12_10(row,col,0);
      col = col - 1;
      if (col < 1) {
        col = 1;
      }
    }
    if (sw==0){
      if (row==x1 && col==y1){
        digitalWrite(LED1,HIGH);
        check1=1;
        Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle1);delay(87);
        Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle2);delay(87);
        Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle3);delay(87);
        Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle4);delay(87);
        Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle1);delay(87);
        Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle2);delay(87);
        Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle3);delay(87);
        Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle4);delay(87);
        Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle1);delay(87);
        Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle2);delay(87);
        Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle3);delay(87);
        Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle4);delay(87);
        Display_MAX721911_12_10(MAX7219_disp_11_12_10_lough);delay(500);
        }
          else if (row==x2 && col==y2){
          digitalWrite(LED2,HIGH);
          check2=1;
          Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle1);delay(87);
          Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle2);delay(87);
          Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle3);delay(87);
          Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle4);delay(87);
          Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle1);delay(87);
          Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle2);delay(87);
          Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle3);delay(87);
          Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle4);delay(87);
          Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle1);delay(87);
          Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle2);delay(87);
          Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle3);delay(87);
          Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle4);delay(87);
           Display_MAX721911_12_10(MAX7219_disp_11_12_10_lough);delay(500);
          }
              else if (row==x3 && col==y3){
            digitalWrite(LED3,HIGH);
            check3=1;
            Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle1);delay(87);
            Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle2);delay(87);
            Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle3);delay(87);
            Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle4);delay(87);
            Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle1);delay(87);
            Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle2);delay(87);
            Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle3);delay(87);
            Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle4);delay(87);
            Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle1);delay(87);
            Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle2);delay(87);
            Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle3);delay(87);
            Display_MAX721911_12_10(MAX7219_disp_11_12_10_circle4);delay(87);
             Display_MAX721911_12_10(MAX7219_disp_11_12_10_lough);delay(500);
                }
              else{
              Display_MAX721911_12_10(MAX7219_disp_11_12_10_fork1);delay(87);
              Display_MAX721911_12_10(MAX7219_disp_11_12_10_fork2);delay(87);
              Display_MAX721911_12_10(MAX7219_disp_11_12_10_fork3);delay(87);
              Display_MAX721911_12_10(MAX7219_disp_11_12_10_fork4);delay(87);
              Display_MAX721911_12_10(MAX7219_disp_11_12_10_fork1);delay(87);
              Display_MAX721911_12_10(MAX7219_disp_11_12_10_fork2);delay(87);
              Display_MAX721911_12_10(MAX7219_disp_11_12_10_fork3);delay(87);
              Display_MAX721911_12_10(MAX7219_disp_11_12_10_fork4);delay(87);
              Display_MAX721911_12_10(MAX7219_disp_11_12_10_fork1);delay(87);
              Display_MAX721911_12_10(MAX7219_disp_11_12_10_fork2);delay(87);
              Display_MAX721911_12_10(MAX7219_disp_11_12_10_fork3);delay(87);
              Display_MAX721911_12_10(MAX7219_disp_11_12_10_fork4);delay(87);
              Display_MAX721911_12_10(MAX7219_disp_11_12_10_cry);delay(500);//踩中地雷 撥放成功動畫,反之則撥放失敗動畫
              }count+=1;    //次數+1
                }
        if ( check1==1 && check2==1 &&check3==1 ){
                Display_MAX721911_12_10(MAX7219_disp_11_12_10_you);delay(500);
                Display_MAX721911_12_10(MAX7219_disp_11_12_10_win);delay(500);   //若三個綠燈全亮,出現you win字樣
                        }
       if (count >=3){
       digitalWrite(LEDa,HIGH);
         if(count >=6){
         digitalWrite(LEDb,HIGH);
           if(count >=9){
           digitalWrite(LEDc,HIGH);
            if(count >=12){
            digitalWrite(LEDd,HIGH);
              if(count >=15){
                if ( check1==1 && check2==1 &&check3==1 ){
                Display_MAX721911_12_10(MAX7219_disp_11_12_10_you);delay(500);
                Display_MAX721911_12_10(MAX7219_disp_11_12_10_win);delay(500);   
                        }
                  else {
                  digitalWrite(LEDe,HIGH);
                  Display_MAX721911_12_10(MAX7219_disp_11_12_10_you);delay(500);
                  Display_MAX721911_12_10(MAX7219_disp_11_12_10_lose);delay(500);  //每加三次次數量一個燈,若第五個燈紅燈亮起,出現you lose字樣
                  }
                }
              }
            }
          }
        }
    MAX7219_xy_draw11_12_10(row,col,1);
    delay(100);

}

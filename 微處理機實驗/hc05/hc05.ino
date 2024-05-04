#include <SoftwareSerial.h>
SoftwareSerial BT(12, 13); // RX | TX
char val;
void setup()
{
 
 Serial.begin(9600);
 Serial.println("bt is ready");
 BT.begin(38400); // HC-05 default speed in AT command more
}
void loop()
{
 if (Serial.available()){
 val=Serial.read();
 BT.print(val);
 }
 if (BT.available()){
 val=BT.read();
 Serial.print(val);
}
}

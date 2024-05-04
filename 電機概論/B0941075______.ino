const byte dataPin = 2;
const byte latchPin = 3;
const byte clockPin = 4;

byte index = 0;
const byte LEDs[10]={
  B01111110,
  B00110000,
  B01101101,
  B01111001,
  B00110011,
  B01011011,
  B01110000,
  B01111111,
  B01110011,
};
void setup() {
  pinMode(dataPin,OUTPUT);
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
}

void loop() {
    digitalWrite(latchPin,LOW);

    shiftOut(dataPin,clockPin,LSBFIRST,LEDs[index]);
     digitalWrite(latchPin,HIGH);
     delay(1000);

     index ++;
     if (index ==10){
      index = 0;}
     }

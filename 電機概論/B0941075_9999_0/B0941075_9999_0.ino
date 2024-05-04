const byte SEG_PIN[4]={8,9,10,11};
const byte NUM_OF_SEG =sizeof(SEG_PIN);
int number=9999;
byte digits[4]={0,0,0,0};
const byte dataPin = 2; 
const byte latchPin = 3;
const byte clockPin = 4;

 unsigned long previousMillis=0;
 const long interval =1000;

 const byte LEDs[10]={
  0x7E, 0x30, 0x6D, 0x79, 0x33,
  0x5B, 0x5F, 0x70, 0x7F, 0x73};
  void counter(){
    unsigned long currentMillis = millis();
  
  if(currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    if (--number < 0){
      number = 9999;}
  digits[0]=number %10;
  digits[1]=number /10 %10;
  digits[2]=number /100 %10;
  digits[3]=number /1000 %10;
  }
  }

  void display(){
    byte num ;
    for (byte i=0; i<NUM_OF_SEG; i++){
      num = digits[i];
      digitalWrite (latchPin,LOW);
      shiftOut(dataPin,clockPin, LSBFIRST, LEDs[num]);
      digitalWrite (latchPin,HIGH);

      digitalWrite (SEG_PIN[i],LOW);
      delay(1);

      for (byte j=0;j<NUM_OF_SEG; j++){
        digitalWrite(SEG_PIN[j],HIGH);
        }
      }
    }
    void setup () {
      pinMode(dataPin,OUTPUT);
      pinMode(latchPin,OUTPUT);
      pinMode(clockPin,OUTPUT);

      for(byte i=0;i<NUM_OF_SEG;i++){
        pinMode(SEG_PIN[i],OUTPUT);
        digitalWrite(SEG_PIN[i],HIGH);
        }
      }
      void loop(){
        counter();
        display();
        }

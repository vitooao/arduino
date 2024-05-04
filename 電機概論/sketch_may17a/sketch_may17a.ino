const byte swPin = 2;
const byte led1 = 7;
const byte led2 = 8;
const byte led3 = 9;
const byte led4 = 10;
const byte led5 = 11;
const byte led6 = 12;
volatile bool state =LOW;
void swISR() {
  state = !state;
  
    digitalWrite(led2,HIGH);
    
  }
void setup() {
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  pinMode(led5,OUTPUT);
  pinMode(led6,OUTPUT);
  digitalWrite(led1,HIGH);
  attachInterrupt(0,swISR,CHANGE);
}

void loop() {

}

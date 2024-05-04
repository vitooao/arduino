const byte GND_PIN1[4]={8,9,10,11};
const byte GND_PIN2[4]={11,10,9,8};

const byte dataPIN=2;
const byte latchPIN=3;
const byte clockPIN=4;

const byte LEDs[6]={
  B1000000,B0100000,B0010000,B0001000,B0000100,B0000010
};


void setup() {
  pinMode(dataPIN,OUTPUT);
  pinMode(latchPIN,OUTPUT);
  pinMode(clockPIN,OUTPUT);
  for(byte j=0; j<4; j++){
    pinMode(GND_PIN1[j],OUTPUT);
    digitalWrite(GND_PIN1[j],HIGH);
    }
}

void loop() {
 
  for(byte i=0 ;i<4;i++){
    digitalWrite(latchPIN,LOW);
    shiftOut(dataPIN,clockPIN,LSBFIRST,LEDs[0]);
    digitalWrite(latchPIN,HIGH);
    digitalWrite(GND_PIN1[i],LOW);
    delay(500);
    digitalWrite(GND_PIN1[i],HIGH);
    
  }
  
    digitalWrite(latchPIN,LOW);
    shiftOut(dataPIN,clockPIN,LSBFIRST,LEDs[1]);
    digitalWrite(latchPIN,HIGH);
    digitalWrite(GND_PIN1[3],LOW);
    delay(500);
    digitalWrite(GND_PIN1[3],HIGH);
   
    
    digitalWrite(latchPIN,LOW);
    shiftOut(dataPIN,clockPIN,LSBFIRST,LEDs[2]);
    digitalWrite(latchPIN,HIGH);
    digitalWrite(GND_PIN1[3],LOW);
    delay(500);
    digitalWrite(GND_PIN1[3],HIGH);
    
    for(byte i=0 ;i<4;i++){
    digitalWrite(latchPIN,LOW);
    shiftOut(dataPIN,clockPIN,LSBFIRST,LEDs[3]);
    digitalWrite(latchPIN,HIGH);
    digitalWrite(GND_PIN2[i],LOW);
    delay(500);
    digitalWrite(GND_PIN2[i],HIGH);
    }

    digitalWrite(latchPIN,LOW);
    shiftOut(dataPIN,clockPIN,LSBFIRST,LEDs[4]);
    digitalWrite(latchPIN,HIGH);
    digitalWrite(GND_PIN1[0],LOW);
    delay(500);
    digitalWrite(GND_PIN1[0],HIGH);
   
    
    digitalWrite(latchPIN,LOW);
    shiftOut(dataPIN,clockPIN,LSBFIRST,LEDs[5]);
    digitalWrite(latchPIN,HIGH);
    digitalWrite(GND_PIN1[0],LOW);
    delay(500);
    digitalWrite(GND_PIN1[0],HIGH);
   
}

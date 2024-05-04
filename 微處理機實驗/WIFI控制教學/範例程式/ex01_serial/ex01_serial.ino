void setup() {

  Serial.begin(9600);
  Serial.println("Ready");
}

void loop() {
  if (Serial.available()>0)
  {
    char data = Serial.read();
    Serial.print("> ");
    Serial.println(data);
  }
}

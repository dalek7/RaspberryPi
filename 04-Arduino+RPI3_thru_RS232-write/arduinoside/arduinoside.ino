void setup() {
  Serial.begin(115200);              //Starting serial communication
  pinMode(LED_BUILTIN, OUTPUT);

}
  
void loop() {
    
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    if(inChar=='0')
      digitalWrite(LED_BUILTIN, LOW);   
    else if (inChar=='1')
      digitalWrite(LED_BUILTIN, HIGH);  
  }
}

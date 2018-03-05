int i =0; 

void setup() {
  Serial.begin(115200);              //Starting serial communication
  pinMode(LED_BUILTIN, OUTPUT);
}
  
void loop() {
  
  //sprintf(dataString,"%02X",a); // convert a value to hexa 
  Serial.println(i);   // send the data
  i = i + 1;
  delay(1000);                  // give the loop some break
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



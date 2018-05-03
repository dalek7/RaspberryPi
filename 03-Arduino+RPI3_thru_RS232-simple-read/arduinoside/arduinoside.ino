int i =0; 

void setup() {
  Serial.begin(115200);              //Starting serial communication
  pinMode(LED_BUILTIN, OUTPUT);
}
  
void loop() {
  
  Serial.println(i);   // send the data
  i = i + 1;
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                  // give the loop some break
  
  Serial.println(i);   // send the data
  i = i + 1;
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second

  if(i>10000)
    i=0;
}

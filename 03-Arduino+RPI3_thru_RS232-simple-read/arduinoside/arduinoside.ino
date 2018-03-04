// http://www.instructables.com/id/Raspberry-Pi-Arduino-Serial-Communication/
char dataString[50] = {0};
int i =0; 

void setup() {
Serial.begin(115200);              //Starting serial communication
}
  
void loop() {
  
  //sprintf(dataString,"%02X",a); // convert a value to hexa 
  Serial.println(i);   // send the data
  i = i + 1;
  delay(1000);                  // give the loop some break
}

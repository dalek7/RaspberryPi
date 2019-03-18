#include <iostream>
#include <wiringPi.h>

// See https://github.com/dalek7/RaspberryPi/blob/master/pi3_gpio.png
#define PIN13 27
#define PIN16 23

using namespace std;
int main (void)
{
  // RPi numbering is very confusing
  int LED1 = PIN13; //GPIO27 - PIN#13
  int LED2 = PIN16; //GPIO23 - PIN#16

  wiringPiSetup () ;
  pinMode (LED1, OUTPUT) ;
  pinMode (LED2, OUTPUT) ;
  for (;;)
  {
    digitalWrite (LED1, HIGH);
    digitalWrite (LED2, LOW);
    delay (500) ;
    cout << "LED ON" << endl;

    digitalWrite (LED1,  LOW);
    digitalWrite (LED2,  HIGH);
    delay (500) ;
    cout << "LED OFF" << endl;
  }
  return 0 ;
}

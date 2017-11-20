#include <iostream>
#include <wiringPi.h>

using namespace std;
int main (void)
{
  wiringPiSetup () ;
  pinMode (0, OUTPUT) ;
  for (;;)
  {
    digitalWrite (0, HIGH) ; delay (500) ;
    cout << "ON" << endl;
    digitalWrite (0,  LOW) ; delay (500) ;
    cout << "OFF" << endl;
  }
  return 0 ;
}

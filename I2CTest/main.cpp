
#include <iostream>
#include <errno.h>
#include <wiringPiI2C.h>

using namespace std;

// MPL115A: 50 to 115kPa, Absolute Digital Pressure Sensor
// https://www.nxp.com/products/sensors/pressure-sensors/barometric-pressure-15-to-115-kpa/50-to-115kpa-absolute-digital-pressure-sensor:MPL115A

void Test1()
{
    for(int i=0; i<128; i++)
    {
        int fd = wiringPiI2CSetup(i);   // It returns a standard file descriptor.

        cout << fd << endl;
    }

}

int main()
{
   int fd, result;
   // Initialize the interface by giving it an external device ID.
   // The MPL115A defaults to address 0x60.
   //
   // It returns a standard file descriptor.
   //
   fd = wiringPiI2CSetup(0x60);
   cout << fd << endl;



    return 0;

}

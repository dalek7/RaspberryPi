
#include <iostream>
#include <errno.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

using namespace std;

// MPL115A: 50 to 115kPa, Absolute Digital Pressure Sensor
// https://www.nxp.com/products/sensors/pressure-sensors/barometric-pressure-15-to-115-kpa/50-to-115kpa-absolute-digital-pressure-sensor:MPL115A
// http://pi4j.com/apidocs/com/pi4j/wiringpi/I2C.html
// based on http://hobbyist86.rssing.com/chan-9523472/latest.php#item13

// MPU9250

void Test1();
void GetSensorValues_MPL115A(float& celsius, float& kPa);

int main()
{
    int fd;
    int cnt;

    while(1)
    {
        // variables for the final results
        float kPa, celsius;
        GetSensorValues_MPL115A(celsius, kPa);
        // (1 hPa = 100 Pa)
        float hPa =  kPa * 0.01;


        //show the results
        printf("%5d) %.f kPa (= %.2f hPa), %.2f degrees in Celsius \n" ,cnt++, kPa, hPa, celsius);

        delay(100);
    }


    return 0;

}




void Test1()
{
    for(int i=0; i<128; i++)
    {
        int fd = wiringPiI2CSetup(i);   // It returns a standard file descriptor.

        cout << fd << endl;
    }

}

void GetSensorValues_MPL115A(float& celsius, float& kPa)
{
    // variables to hold the integer values of coefficients
    int16_t a0coeff;
    int16_t b1coeff;
    int16_t b2coeff;
    int16_t c12coeff;
    // variables to hold the floating point coefficients
    float a0;
    float b1;
    float b2;
    float c12;
    // some intermediate values
    int pressure, temp;
    float pressureComp;

    // open a file descriptor to the device on the I2C bus
    int fd = wiringPiI2CSetup(0x60);  // 0x60 is bus address of mpl115a2
    if (fd==-1)
    {
        printf("wiringPiI2CSetup failed\n");
        return ;
    }


    // get the coefficients.  This only needs to be done once.
    // Note on C language: the << and >> operators perform bit shifting
    a0coeff = (( (uint16_t) wiringPiI2CReadReg8(fd,4) << 8) | wiringPiI2CReadReg8(fd,5));
    b1coeff = (( (uint16_t) wiringPiI2CReadReg8(fd,6) << 8) | wiringPiI2CReadReg8(fd,7));
    b2coeff = (( (uint16_t) wiringPiI2CReadReg8(fd,8) << 8) | wiringPiI2CReadReg8(fd,9));
    c12coeff = (( (uint16_t) (wiringPiI2CReadReg8(fd,10) << 8) | wiringPiI2CReadReg8(fd,11))) >> 2;
    //printf("%d   %d   %d   %d\n",a0coeff,b1coeff,b2coeff,c12coeff);
    // convert coefficients to floating point
    a0 = (float)a0coeff / 8;
    b1 = (float)b1coeff / 8192;
    b2 = (float)b2coeff / 16384;
    c12 = (float)c12coeff;
    c12 /= 4194304.0;
    //printf("%f   %f   %f   %f\n\n",a0,b1,b2,c12);

    // start conversion and wait a tiny bit
    wiringPiI2CWriteReg8(fd,0x12,0);
    delay(5);

    // get the results by reading the device registers
    pressure = (( (uint16_t) wiringPiI2CReadReg8(fd,0) << 8) | wiringPiI2CReadReg8(fd,1)) >> 6;
    temp = (( (uint16_t) wiringPiI2CReadReg8(fd,2) << 8) | wiringPiI2CReadReg8(fd,3)) >> 6;

    // compute temperature compensation for pressure
    pressureComp = a0 + (b1 + c12 * temp ) * pressure + b2 * temp;

    // get the pressure in kiloPascals
    kPa = ((65.0F / 1023.0F) * pressureComp) + 50.0F;        // kPa
    // get the temperature in celsius degrees
    celsius = ((float) temp - 498.0F) / -5.35F +25.0F;        // C

    // convert kilo-Pascals to inches of mercury
    //float baro2 =  baro * 0.295299830714;

    // (1 hPa = 100 Pa)
    //float hPa =  baro * 0.01;

    // convert Celsius to Farenheit
    //farenheit = (celsius * 1.8) + 32.0;


}

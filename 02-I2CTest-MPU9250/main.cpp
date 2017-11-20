
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

// https://github.com/simondlevy/RPi_MPU9250/blob/master/examples/Basic_I2C/Basic_I2C.cpp

using namespace std;

// MPU9250
#include "MPU9250.h"

float ax, ay, az, gx, gy, gz, hx, hy, hz, t;
int beginStatus;

// an MPU9250 object with its I2C address
// of 0x68 (ADDR to GRND) and on Teensy bus 0
/*
$ sudo i2cdetect -y 1
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00:          -- -- -- -- -- -- -- -- -- -- -- -- --
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
60: -- -- -- -- -- -- -- -- 68 -- -- -- -- -- -- --
70: -- -- -- -- -- -- -- --
*/
MPU9250 IMU(0x68);

void setup();
void loop();
void printData();

int main()
{
    int fd;
    int cnt;

    setup();
    cout << "Hello !" << endl;
    while(1)
    {
        loop();
        delay(20);
    }


    return 0;

}


void loop()
{
  if(beginStatus < 0)
  {
    delay(1000);
    fprintf(stderr, "IMU initialization unsuccessful\n");
    fprintf(stderr, "Check IMU wiring or try cycling power\n");
    delay(10000);
  }
  else
  {
    /* get the individual data sources */
    /* This approach is only recommended if you only
     *  would like the specified data source (i.e. only
     *  want accel data) since multiple data sources
     *  would have a time skew between them.
     */
    // get the accelerometer data (m/s/s)
    IMU.getAccel(&ax, &ay, &az);

    // get the gyro data (rad/s)
    IMU.getGyro(&gx, &gy, &gz);

    // get the magnetometer data (uT)
    //IMU.getMag(&hx, &hy, &hz);

    // get the temperature data (C)
    //IMU.getTemp(&t);

    // print the data
    printData();
    return ;
    // delay a frame
    //delay(50);

    /* get multiple data sources */
    /* In this approach we get data from multiple data
     *  sources (i.e. both gyro and accel). This is
     *  the recommended approach since there is no time
     *  skew between sources - they are all synced.
     *  Demonstrated are:
     *  1. getMotion6: accel + gyro
     *  2. getMotion7: accel + gyro + temp
     *  3. getMotion9: accel + gyro + mag
     *  4. getMotion10: accel + gyro + mag + temp
     */

     /* getMotion6 */
    // get both the accel (m/s/s) and gyro (rad/s) data
    IMU.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    // get the magnetometer data (uT)
    IMU.getMag(&hx, &hy, &hz);

    // get the temperature data (C)
    IMU.getTemp(&t);

    // print the data
    printData();

    // delay a frame
    delay(50);

    /* getMotion7 */
    // get the accel (m/s/s), gyro (rad/s), and temperature (C) data
    IMU.getMotion7(&ax, &ay, &az, &gx, &gy, &gz, &t);

    // get the magnetometer data (uT)
    IMU.getMag(&hx, &hy, &hz);

    // print the data
    printData();

    // delay a frame
    delay(50);

    /* getMotion9 */
    // get the accel (m/s/s), gyro (rad/s), and magnetometer (uT) data
    IMU.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &hx, &hy, &hz);

    // get the temperature data (C)
    IMU.getTemp(&t);

    // print the data
    printData();

    // delay a frame
    delay(50);

    // get the accel (m/s/s), gyro (rad/s), and magnetometer (uT), and temperature (C) data
    IMU.getMotion10(&ax, &ay, &az, &gx, &gy, &gz, &hx, &hy, &hz, &t);

    // print the data
    printData();

    // delay a frame
    delay(50);
  }
}

void setup()
{

  // start communication with IMU and
  // set the accelerometer and gyro ranges.
  // ACCELEROMETER 2G 4G 8G 16G
  // GYRO 250DPS 500DPS 1000DPS 2000DPS
  beginStatus = IMU.begin(ACCEL_RANGE_4G,GYRO_RANGE_250DPS);
}

void printData()
{

  // print the data
  printf("%6.6f\t", ax);
  printf("%6.6f\t", ay);
  printf("%6.6f\t", az);

  printf("%6.6f\t", gx);
  printf("%6.6f\t", gy);
  printf("%6.6f\t\n", gz);
/*
  printf("%6.6f\t", hx);
  printf("%6.6f\t", hy);
  printf("%6.6f\t", hz);
*/
  //printf("%6.6f\n", t);
}

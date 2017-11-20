
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
#include <vector>

#include <thread>
#include <atomic>

typedef struct Inertial
{
    //float ax, ay, az, gx, gy, gz, hx, hy, hz, t;
    float ax, ay, az, gx, gy, gz, msec;

}__Inertial;


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
std::vector <Inertial> mvTraj;
void setup();
void GetSensorValues();
void printData();
std::string GetTimeString();
void loop();
long cnt=0;

// A flag to indicate whether a key had been pressed.
atomic_bool keyIsPressed(false);



int main()
{

    setup();
    cout << "Hello !" << endl;
    cout << GetTimeString() <<endl;

    // Create a thread for the loop.
    thread loopThread = thread(loop);

// Wait for user input (single character). This is OS dependent.
#ifdef _WIN32 || _WIN64
    system("pause");
#else
    system("read -n1");
#endif
    // Set the flag with true to break the loop.
    keyIsPressed = false;
    // Wait for the thread to finish.
    loopThread.join();

    cout << "Done" <<endl;

    return 0;


}

// The function that has the loop.
void loop()
{
    while (!keyIsPressed) {
        // Do whatever
        cout << cnt << endl;
        GetSensorValues();
        delay(20);
        cnt++;

        if(cnt ==200)
        {
            std::string fn1= "out/out_"+GetTimeString()+".txt";
            cout <<"Saving " << mvTraj.size() <<" samples .." << endl;

            FILE *fp = fopen(fn1.c_str(), "w+");

            for(int i=0; i<mvTraj.size(); i++)
            {
                Inertial v = mvTraj[i];
                fprintf(fp, "%d\t%f\n", cnt, v.ax);
            }
            fclose(fp);
            cout << fn1 <<endl;
            mvTraj.clear();
            break;

            cnt = 0;
        }
    }
}


void GetSensorValues()
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

    Inertial v;
    v.ax = ax;
    v.ay = ay;
    v.az = az;
    v.gx = gx;
    v.gy = gy;
    v.gz = gz;
    v.msec = 0; // fix this

    mvTraj.push_back(v);

/*
    Inertial v;
    v.ax = ax;


    mvTraj.push_back(v);*/
    // get the magnetometer data (uT)
    //IMU.getMag(&hx, &hy, &hz);

    // get the temperature data (C)
    //IMU.getTemp(&t);

    // print the data
    printData();

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



#ifdef _WINDOWS
#include <time.h>
#else
#include <sys/time.h>
#endif

std::string GetTimeString()
{

    string str1;
    // only for Windows
    #ifdef _WINDOWS
        SYSTEMTIME st;
        GetSystemTime(&st);
        str1 = string_format("%d%02d%02d_%02d%02d%02d_%03d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
    #else
        time_t t = time(0);   // get time now
        struct tm * now = localtime( & t );
        struct timeval ts;
        gettimeofday(&ts,0);
        double tu = ts.tv_usec;

        char buf[255];
        sprintf(buf, "%d%02d%02d_%02d%02d%02d_%.f",    now->tm_year + 1900,
                                                                now->tm_mon + 1,
                                                                now->tm_mday,
                                                                now->tm_hour,
                                                                now->tm_min,
                                                                now->tm_sec,
                                                                    tu);
        str1 = std::string(buf);

    #endif





    return str1;

}





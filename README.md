# RaspberryPi

### Example
<img src='./99-Lab/3DModels/Case_7Segment_v1/20191008_165328.jpg' width=500px/>

### Numbering
* Difference between BOARD and BCM for GPIO pin numbering 
```
https://raspberrypi.stackexchange.com/a/12967
```

### Setting up the wiringPI
```
http://wiringpi.com/download-and-install/
```

###
```
NOTE: To compile programs with wiringPi, you need to add:
    -lwiringPi
```

### Scanning an I2C bus for devices
```
i2cdetect -y 1
```

### Installing Adafruit_Python_LED_Backpack library
```
git clone https://github.com/adafruit/Adafruit_Python_LED_Backpack.git
cd Adafruit_Python_LED_Backpack
sudo python setup.py install
```
### PI3 GPIO
<img src='pi3_gpio.png' width = '400px'/>

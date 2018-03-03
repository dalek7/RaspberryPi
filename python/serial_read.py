import numpy as np
import serial
import os

if os.name =='nt':
    print('Detected WIndows')
    ser = serial.Serial('COM4',115200)
else:
    ser = serial.Serial(
        port='/dev/ttyACM0',  # /dev/ttyACM0
        baudrate=115200,  # 9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
    )
   #ser = serial.Serial('/dev/ttyUSB0',9600)


while True:
   x = ser.readline()
   x = x.strip()
   if len(x)>0 :
      #print(x, len(x))
	  print('Received: {}'.format(x))
	#print read_serial
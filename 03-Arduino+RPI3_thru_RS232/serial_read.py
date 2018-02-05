import time
import serial


ser = serial.Serial(
  
   port='/dev/ttyACM0',#/dev/ttyACM0
   baudrate = 115200,#9600,
   parity=serial.PARITY_NONE,
   stopbits=serial.STOPBITS_ONE,
   bytesize=serial.EIGHTBITS,
   timeout=1
)
counter=0


while 1:
   x=ser.readline()
   x = x.strip()
   if len(x)>0 :
      print(x, len(x))
   #for i in range(0, len(x)):
   # print(x[i], len(x[i]))
	
   #if len(x)<2:
   #   print x.strip()
      #print (ord(x))

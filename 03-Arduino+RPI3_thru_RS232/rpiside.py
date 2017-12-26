import serial

ser = serial.Serial('/dev/ttyUSB0',115200)#
s = [0]
cnt = 0
while True:
	#read_serial=ser.readline()
        s[0] = str(int (ser.readline(),16))
	print(cnt, s[0])
        cnt = cnt + 1
	#print read_serial

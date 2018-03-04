import serial
import os

if os.name =='nt':
    print('Detected Windows')
    port = "COM4"

else:
    port='/dev/ttyACM0',  # /dev/ttyACM0

ser = serial.Serial(port, 115200, timeout=1)

# open the serial port
if ser.isOpen():
    print(ser.name + ' is open...')

while True:
    cmd = raw_input("Enter command or 'exit':")
    # for Python 2
    # cmd = input("Enter command or 'exit':")
    # for Python 3
    if cmd == 'exit':
        ser.close()
        exit()
    else:
        ser.write(cmd.encode('ascii') + '\r\n')
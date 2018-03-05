# https://gordonlesti.com/use-tkinter-without-mainloop/
# Seung-Chan Kim
# Receiving serial data + Tkinter
from Tkinter import *

import threading
import serial

import os
import platform

#print os.name
#print platform.system()

if os.name =='nt':
    print('Detected Windows')
    port = "COM4"
elif os.name =='posix':
    if platform.system() == 'Darwin':
        print('Detected MAC')
        #port = "/dev/tty.usbmodem14511"
        port = "/dev/tty.usbmodem14311" # Arduino MEGA @LAB #1

    else: # 'Linux' including RPI
        print('Detected Linux (including RPI3)')
        port='/dev/ttyACM0',  # /dev/ttyACM0

else: # Linux
    port='/dev/ttyACM0',  # /dev/ttyACM0


print('Connecting to ... {}'.format(port))
ser = serial.Serial(port, 115200, timeout=1)

# open the serial port
if ser.isOpen():
    print(ser.name + ' is open...')

bLed = True
loop_active = True
def ledON():
    global bLed
    print("LED button pressed")
    if bLed :
        ser.write('1')
        ledButton["text"] = "LED OFF"

    else:
        ser.write('0')
        ledButton["text"] = "LED ON"

    bLed = not bLed

def exitProgram():
    global loop_active
    print("Exit Button pressed")
    loop_active = False
    #ROOT.quit()
    #ROOT.update()

class App(threading.Thread):

    def __init__(self, tk_root):
        self.root = tk_root
        threading.Thread.__init__(self)
        self.start()

    def run(self):
        global loop_active
        #loop_active = True
        while loop_active:
            x = ser.readline()
            x = x.strip()
            if len(x) > 0:
                # print(x, len(x))
                print('Received: {}'.format(x))
                text1.set('Received: {}'.format(x))

        self.root.quit()
        self.root.update()

ROOT = Tk()
APP = App(ROOT)

text1 = StringVar()
text1.set('Ready...')

ledButton = Button(ROOT, text = "LED ON", command = ledON, height = 2, width =8 )
ledButton.pack()

lb = Label(ROOT, textvariable=text1)
lb.pack()

exitButton  = Button(ROOT, text = "Exit", command = exitProgram, height =2 , width = 6)
exitButton.pack(side = BOTTOM)

ROOT.title("Hello")
ROOT.geometry('200x100')

ROOT.mainloop()
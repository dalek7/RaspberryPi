from Tkinter import *
import tkFont
import serial
import os

print os.name

if os.name =='nt':
    print('Detected Windows')
    port = "COM4"
elif os.name =='posix':
    print('Detected MAC')
    port = "/dev/tty.usbmodem14511"
else:
    port='/dev/ttyACM0',  # /dev/ttyACM0

ser = serial.Serial(port, 115200, timeout=1)

# open the serial port
if ser.isOpen():
    print(ser.name + ' is open...')

win = Tk()
myFont = tkFont.Font(family = 'Calibri', size = 36) #, weight = 'bold'

bLed = True
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
    print("Exit Button pressed")
    win.quit()


win.title("First GUI")
win.geometry('800x480')

exitButton  = Button(win, text = "Exit", font = myFont, command = exitProgram, height =2 , width = 6)
exitButton.pack(side = BOTTOM)

ledButton = Button(win, text = "LED ON", font = myFont, command = ledON, height = 2, width =8 )
ledButton.pack()

mainloop()

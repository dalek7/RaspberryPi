#import Tkinter # https://raspberrypi.stackexchange.com/a/76700
#from Tkinter import * # py2 # https://stackoverflow.com/a/38309119
# written by Seung-Chan
# TODO : add display (i2c)
# TODO : UI alignment (buttons)

from tkinter import * # py3
import threading
import RPi.GPIO as GPIO
import time
import datetime

    
def dutyUp():
    global dr
    global p
    print("Duty up")
    if dr<95:
        dr = dr + 5
        p.ChangeDutyCycle(dr)        

def dutyDn():
    global dr
    global p
    print("Duty down")
    if dr>5:
        dr = dr - 5
        p.ChangeDutyCycle(dr)  

# TODO : fix this !
def exitProgram():
    global p
    global GPIO
    global loop_active
    
    p.stop()
    
    loop_active = False
    

    GPIO.cleanup()

cnt1 = 0
class App(threading.Thread):

    def __init__(self, tk_root):
        self.root = tk_root
        threading.Thread.__init__(self)
        self.start()

    def run(self):
        global loop_active
        global cnt1
        global dr
        #loop_active = True
        while loop_active:
            
            time.sleep(0.1)
            #s1 = datetime.datetime.now().strftime("%Y%m%d-%H:%M:%S")
            #s1 = '{}'.format(cnt1)
            s1 = '{}'.format(dr)
            text1.set(s1)
            cnt1 = cnt1+1
            
        self.root.quit()
        self.root.update()
        

loop_active = True

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
GPIO.setup(12, GPIO.OUT)

freq = 1000
p = GPIO.PWM(12, freq)  # channel=12 frequency=50Hz
dr = 50 # duty ratio
p.start(dr) # duty (0~99)


ROOT = Tk()
APP = App(ROOT)

text1 = StringVar()
text1.set(datetime.datetime.now().strftime("%Y/%m/%d %H:%M:%S"))

btnUp = Button(ROOT, text = "Up", command = dutyUp, height = 2, width =8 )
btnUp.pack()

btnDn = Button(ROOT, text = "Down", command = dutyDn, height = 2, width =8 )
btnDn.pack()

lb = Label(ROOT, textvariable=text1)
lb.pack()

exitButton  = Button(ROOT, text = "Exit", command = exitProgram, height =2 , width = 6)
exitButton.pack()

ROOT.title("Hello")
ROOT.geometry('320x240')

ROOT.mainloop()






from Tkinter import *
import tkFont
win = Tk()
myFont = tkFont.Font(family = 'Calibri', size = 36) #, weight = 'bold'

def ledON():
	print("LED button pressed")


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

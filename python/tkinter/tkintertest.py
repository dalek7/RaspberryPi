# https://gordonlesti.com/use-tkinter-without-mainloop/
from Tkinter import *
import threading

class App(threading.Thread):

    def __init__(self, tk_root):
        self.root = tk_root
        threading.Thread.__init__(self)
        self.start()

    def run(self):
        loop_active = True
        while loop_active:
            user_input = raw_input("Give me your command! Just type \"exit\" to close: ")
            if user_input == "exit":
                loop_active = False
                self.root.quit()
                self.root.update()
            else:
                label = Label(self.root, text=user_input)
                label.pack()

ROOT = Tk()
APP = App(ROOT)
LABEL = Label(ROOT, text="Hello, world!")
LABEL.pack()
ROOT.mainloop()
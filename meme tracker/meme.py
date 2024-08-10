
import sys
import subprocess
from threading import Thread
from multiprocessing import Process
from queue import Queue

import time
from typing import IO

import tkinter


from tkinter import Tk, Button, Frame
from tkinter.scrolledtext import ScrolledText


def enqueue_output(out : IO[bytes], queue : Queue):
    while True:
        i = out.read(1)
        queue.put(i)

class procMonger:
    def __init__(self, process) -> None:
        self.inpQueue = Queue()
        self.outQueue = Queue()
        self.errQueue = Queue()

        self.proc = subprocess.Popen(process,
                                     stdin=subprocess.PIPE,
                                     stdout=subprocess.PIPE,
                                     stderr=subprocess.PIPE,
                                     
        )

        self.outThread = Thread(target=enqueue_output, args=(self.proc.stdout, self.outQueue))
        self.errThread = Thread(target=enqueue_output, args=(self.proc.stderr, self.errQueue))

        self.outThread.daemon = True;
        self.errThread.daemon = True;

        self.outThread.start()
        self.errThread.start()

    def waitFor(self, text):
        outStr = ""
        while text not in outStr:
            while self.outQueue.empty() == False:
                outStr += self.outQueue.get_nowait().decode()
        return outStr

    def getOutput(self):
        outStr = ""
        while self.outQueue.empty() == False:
            outStr += self.outQueue.get_nowait().decode()
        return outStr

    def getError(self):
        outStr = ""
        while self.errQueue.empty() == False:
            outStr += self.errQueue.get_nowait().decode()
        return outStr

    def write(self, text):
        self.proc.stdin.write((text).encode())
        self.proc.stdin.flush()

printQueue = Queue()

class PrintLogger(object):  # create file like object

    def __init__(self, textbox, root):  # pass reference to text widget
        self.textbox = textbox  # keep ref
        self.root = root

    def write(self, text):
        printQueue.put(text)
        self.root.event_generate("<<printEv>>", when="tail", state=123)
        time.sleep(0.001)

    def flush(self):  # needed for file like object
        pass

class MainGUI(Tk):

    def __init__(self):
        Tk.__init__(self)
        self.root = Frame(self)
        self.root.pack()
        # self.redirect_button = Button(self.root, text="Redirect console to widget", command=self.redirect_logging)
        # self.redirect_button.pack()
        # self.redirect_button = Button(self.root, text="Redirect console reset", command=self.reset_logging)
        # self.redirect_button.pack()
        # self.test_button = Button(self.root, text="Test Print", command=self.test_print)
        # self.test_button.pack()
        self.log_widget = ScrolledText(self.root, height=50, width=140, font=("consolas", "8", "normal"))
        self.log_widget.pack()

    def reset_logging(self):
        sys.stdout = sys.__stdout__
        sys.stderr = sys.__stderr__

    def test_print(self):
        print("Am i working?")

    def redirect_logging(self):
        logger = PrintLogger(self.log_widget, self.root)
        sys.stdout = logger
        sys.stderr = logger

    def eventPrint(self, evt):
        # if printQueue.empty() == False:
        self.log_widget.configure(state="normal")  # make field editable
        self.log_widget.insert("end", printQueue.get_nowait())  # write text to
        self.log_widget.see("end")  # scroll to end
        self.log_widget.configure(state="disabled")  # make field readonly
        self.update()

def main():
    print("""Automatic memory checker V0.1""");

    gdb = procMonger("gdb test.exe")
    print(gdb.waitFor("(gdb)"))

    # gdb.write("starti\n")
    gdb.write("break main\n")
    print(gdb.waitFor("(gdb)"))

    gdb.write("run main\n")
    print(gdb.waitFor("(gdb)"))

    for i in range(80):
        gdb.write("step\n")
        print(gdb.waitFor("(gdb)"))


if __name__ == "__main__":

    execThread = Thread(target=main)

    execThread.daemon = True

    app = MainGUI()
    app.redirect_logging()
    execThread.start()

    app.bind("<<printEv>>", app.eventPrint)
    app.mainloop()




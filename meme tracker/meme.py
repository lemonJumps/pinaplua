
import sys
import subprocess
from threading import Thread
from multiprocessing import Process
from queue import Queue

import time
from typing import IO

from gdbParser import *
from cParser import *
from memoryValidator import *

from tkinter import *
from tkinter.scrolledtext import ScrolledText

from pprint import pprint

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

class MainGUI(Tk):

    def __init__(self):
        Tk.__init__(self)
        self.root = Frame(self)
        self.root.grid(row=0, column=0, sticky=N+E+S+W)
        self.stackCanvas = Canvas(self.root, width=400, height=400, bg='black')
        self.stackCanvas.grid(row = 0, column = 0, pady = 2)
        self.heapCanvas = Canvas(self.root, width=400, height=400, bg='black')
        self.heapCanvas.grid(row = 1, column = 0, pady = 2)

    def eventPrint(self, evt):
        # if printQueue.empty() == False:
        self.log_widget.configure(state="normal")  # make field editable
        while printQueue.empty() == False:
            self.log_widget.insert("end", printQueue.get())  # write text to
        self.log_widget.see("end")  # scroll to end
        self.log_widget.configure(state="disabled")  # make field readonly
        self.update()

def main(gui : MainGUI):
    parser = Parser()
    memVal = memoryValidator(gui.heapCanvas, gui.stackCanvas)
    cparser = CParser()

    print("""Automatic memory checker V0.1""");

    gdb = procMonger("gdb test.exe")
    print(gdb.waitFor("(gdb)"))

    # gdb.write("starti\n")
    gdb.write("break main\n")
    print(gdb.waitFor("(gdb)"))

    gdb.write("run main\n")
    p = gdb.waitFor("(gdb)")
    parser.parseGDB(p)

    for i in range(100):
        gdb.write("step\n")
        p = gdb.waitFor("(gdb)")
        parser.parseGDB(p)

        gdb.write("info registers\n")
        p = gdb.waitFor("(gdb)")
        parser.parseReg(p)

        cparser.parseFile(parser.file)
        print(cparser.dbgHintsByLine[parser.file][int(parser.line)])
        t : cindex.Token = cparser.tokensByLine[parser.file][int(parser.line)][0] 

        for child in t.cursor.get_arguments():
            print(child.kind, child.spelling)

        gui.update()
        print(parser.file, parser.line, parser.function)

if __name__ == "__main__":

    app = MainGUI()
    # app.redirect_logging()
    execThread = Thread(target=main, args=[app])

    execThread.daemon = True
    execThread.start()

    app.bind("<<printEv>>", app.eventPrint)
    app.mainloop()




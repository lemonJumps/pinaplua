
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

from pprint import pprint

from sdl2 import *
import ctypes

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

def main(surface):
    parser = Parser()
    memVal = memoryValidator()
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

    for i in range(5):
        gdb.write("step\n")
        p = gdb.waitFor("(gdb)")
        parser.parseGDB(p)

        gdb.write("info registers\n")
        p = gdb.waitFor("(gdb)")
        parser.parseReg(p)

        cparser.parseFile(parser.file)
        # print(cparser.dbgHintsByLine[parser.file][int(parser.line)])
        cparser.parseLine(parser.file, parser.line, surface)

        # gui.update()
        print(parser.file, parser.line, parser.function)

if __name__ == "__main__":

    # app.redirect_logging()

    SDL_Init(SDL_INIT_VIDEO)
    window = SDL_CreateWindow(b"Hello World",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              640, 480, SDL_WINDOW_SHOWN)
    windowsurface = SDL_GetWindowSurface(window)

    execThread = Thread(target=main, args=[windowsurface])

    execThread.daemon = True
    execThread.start()

    running = True
    event = SDL_Event()
    while running:
        while SDL_PollEvent(ctypes.byref(event)) != 0:
            if event.type == SDL_QUIT:
                running = False
                break

        SDL_UpdateWindowSurface(window)

    #gpu loop




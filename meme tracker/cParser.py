import clang.cindex as cindex
import clang

import pathlib

from sdl2 import *
import sdl2.ext
import ctypes

import numpy


class CParser:
    def __init__(self) -> None:
        self.tokens = {}
        self.tokensByLine = {}
        self.dbgHintsByLine = {}

        self.a = 0;
        self.b = 0;

    def parseFile(self, fileName):
        if fileName not in self.tokens:



            self.tokens[fileName] = # TODO fill me up

            self.tokensByLine[fileName] = {}
            self.dbgHintsByLine[fileName] = {}
            for token in self.tokens[fileName]:
                token : cindex.Token

                line = token.location.line  
                if line not in self.tokensByLine[fileName]:
                    self.tokensByLine[fileName][line] = []
                    self.dbgHintsByLine[fileName][line] = []

                self.tokensByLine[fileName][line].append(token)

                self.dbgHintsByLine[fileName][line].append(str(token.kind) + " " + str(token.spelling) + " " + str(token.cursor.spelling))

    def parseLine(self, file, line, surface):


        SDL_LockSurface(surface)

        dbg = sdl2.ext.pixels2d(surface)

        tabbs = []
        stack = []

        for token in self.tokensByLine[file][int(line)]:
            tabbs.append(1)
            stack.append(token.cursor)
                
        while stack:
            tab = tabbs.pop()
            v : cindex.Cursor = stack.pop()
            for child in v.get_children():
                child : cindex.Cursor

                # 

                # if child.location.line == int(line):
                stack.append(child)
                tabbs.append(tab + 1)
                
            print("\t"*tab, v.kind, v.spelling, v.displayname, v.location.line, v.access_specifier)
            dbg[self.a, tab + self.b] = 0x00ffffff;

            self.a += 1;
            if self.a >= 640:
                self.a = 0
                self.b += 10
                if self.b >= 480:
                    self.b = 0
                    dbg[:,:] = 0

                
        self.a = 0
        self.b += 10

        if self.b >= 480:
            self.b = 0
            dbg[:,:] = 0

        SDL_LockSurface(surface)
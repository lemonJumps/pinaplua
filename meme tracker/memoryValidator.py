from tkinter import Canvas

class memoryValidator():
    def __init__(self, heapCanvas : Canvas, stackCanvas : Canvas) -> None:
        self.heapCanvas = heapCanvas
        self.stackCanvas = stackCanvas

        self.heapObjects = {}

        self.stackObjects = {}

    def setStackBegin(self, address):
        pass

    def setHeapBegin(self, address):
        pass

    def stackObjCreated(self, address, size):
        pass

    def stackObjDestroyed(self, address):
        pass


    def heapObjCreated(self, address, size):
        pass

    def heapObjDestroyed(self, address):
        pass


    def objAccessedRead(self, address, size):
        pass

    def objAccessedWrite(self, address, size):
        pass


    def setPointer(self, address):
        pass

    def stackPtr(self, address):
        pass
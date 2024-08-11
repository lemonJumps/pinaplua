import re

class Parser:
    def __init__(self) -> None:
        self.function = "(unknown)"
        self.file = "(unknown)"
        self.line = 0

        self.registers = {}

    def parseFunc(self, text : str):
        items = text.split(maxsplit=1)
        self.line = items[0]
        restOfLine = items[1]

        print(restOfLine)

        # parse assignments

        # parse malloc calloc and free


    def parseFile(self, text : str):
        at = text.find(" at ")
        func = text[0:at]
        file, line = text[at+4:-1].rsplit(":", maxsplit=1)

        self.function = re.findall(r"(.+) \(", func)[0].split()[-1]
        self.file = file

    
    def parseGDB(self, output : str):
        lines = output.splitlines()
        if len(lines) >= 3:
            self.parseFile(lines[-3])
            self.parseFunc(lines[-2])

        if len(lines) == 2:
            self.parseFunc(lines[0])

    def parseReg(self, output : str):
        lines = output.splitlines()
        for line in lines[:-2]:
            sl = line.split()
            # print(sl)
            self.registers[sl[0]] = int(sl[1], 0)
        
        # print(self.registers)
        # return lines
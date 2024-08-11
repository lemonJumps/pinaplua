import re

class Parser:
    def __init__(self) -> None:
        self.function = "(unknown)"
        self.file = "(unknown)"
        self.line = 0

    def parseFunc(self, text : str):
        items = text.split(maxsplit=1)
        self.line = items[0]
        restOfLine = items[1]

        print(restOfLine)

    def parseFile(self, text : str):
        at = text.find(" at ")
        func = text[0:at]
        file, line = text[at+4:-1].rsplit(":", maxsplit=1)

        self.function = re.findall(r"(.+) \(", func)[0]
        self.file = file

    
    def parseGDB(self, output : str):
        lines = output.splitlines()

        if len(lines) == 3:
            self.parseFile(lines[0])
            self.parseFunc(lines[1])

        if len(lines) == 2:
            self.parseFunc(lines[0])


        # return lines

from pathlib import Path
import colorama

class ASTnode:
    def __init__(self, name = None, kind = None, varType = None) -> None:
        self.children = []
        self.parent = None
        self.type = varType
        self.name = name
        self.kind = kind

    def __str__(self) -> str:
        return "[name: {}, type: {}, kind {}]".format(self.name, self.type, self.kind)

class Parser:
    def __init__(self) -> None:
        self.roots = {}

        self.nodes = []

        self.tokens = []
        self.file = None

        colorama.init()

    def parseTokens(self, i, tokens) -> ASTnode:
        line = i
        priority = 60
        return [line, priority, ASTnode()]

    def accumulateToken(self, char) -> list:
        return []

    def parseFile(self, file):
        self.file = file

        contents = ""
        with Path(file).open(encoding="utf-8") as f:
            contents = f.read()

        for c in contents:
            self.tokens += self.accumulateToken(c)

        for i, t in enumerate(self.tokens):
            r = self.tokenToNode(i, t)
            if r == None: continue
            print(colorama.Fore.GREEN)
            print(r)
            print(colorama.Fore.RESET)

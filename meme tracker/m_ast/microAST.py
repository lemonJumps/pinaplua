
from pathlib import Path

class ASTnode:
    def __init__(self) -> None:
        self.operands = []
        self.operator = None
        self.kind = "default"

class Parser:
    def __init__(self) -> None:
        self.roots = {}

        self.nodes = []

        self.tokens = []
        self.file = None

    def tokenToNode(self, i, token) -> ASTnode:
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
            l, p, node = self.tokenToNode(i, t)

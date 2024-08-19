import json
import pathlib

ROOT = pathlib.Path(__file__).parent

class Token:
    priority = -1
    association = "LR"
    unary = False
    prefix = False
    # suffix contain
    suffix = False
    # signifies that this is a brace :P
    brace = False
    closingBrace = ""
    # ugh inline ternary, if else block
    ternaryCond = False
    # skips creating node, gives consumed nodes to the parent node
    separator = False

    def __init__(self, text, priority) -> None:
        self.priority = priority
        self.text = text

    def __str__(self) -> str:
        return "token: " + \
            self.text.ljust(10) + \
            str(self.unary).ljust(9) + \
            str(self.prefix).ljust(9) + \
            str(self.suffix).ljust(9) + \
            str(self.brace).ljust(9) + \
            self.closingBrace.ljust(9) + \
            str(self.ternaryCond).ljust(9) + \
            str(self.separator).ljust(9)
    
    def __repr__(self):
        return str(self)

class MicroAST:
    def __init__(self, jsonFile) -> None:
        with (ROOT / jsonFile).open() as f:
            contents = json.load(f)

        self.name = contents["langName"]
        self.version = contents["version"]
        self.fileVersion = contents["fileVersion"]

        self.langSpec = contents["langSpec"]
        self.tokens = {}
        for id, tokens in contents["tokens"].items():
            self.tokens[int(id)] = []
            for token in tokens:
                if type(token) is str:
                    tk = Token(token, id)
                    self.tokens[int(id)].append(tk)
                elif type(token) is list:
                    tk = Token(token[0], id)

                    for item in token[1:]:
                        if item == "prefix":
                            tk.prefix = True
                        elif item == "suffix":
                            tk.suffix = True
                        elif item == "unary":
                            tk.unary = True
                        elif item == "ternaryCond":
                            tk.ternaryCond = True
                        elif item == "separator":
                            tk.separator = True
                        elif item[0:5] == "brace":
                            tk.brace = True
                            tk.closingBrace = item[7:]
                        elif item[0:5] == "assoc":
                            tk.association = item[7:]

                    self.tokens[int(id)].append(tk)

        for id, param in contents["tokenGroupParams"].items():
            for token in self.tokens[int(id)]:
                for item in param:
                    if item == "prefix":
                        tk.prefix = True
                    elif item == "suffix":
                        tk.suffix = True
                    elif item == "unary":
                        tk.unary = True
                    elif item == "ternaryCond":
                        tk.ternaryCond = True
                    elif item == "separator":
                        tk.separator = True
                    elif item[0:5] == "brace":
                        tk.brace = True
                        tk.closingBrace = item[7:]
                    elif item[0:5] == "assoc":
                        tk.association = item[7:]


        self.keywords = contents["keywords"]

if __name__ == "__main__":
    m = MicroAST("c_tokens.json")

    print("Language Name:", m.name)
    print("Language Version:", m.version)
    print("File Version:",m.fileVersion)
    print("language specification:",m.langSpec)
    print("tokens:")
    print("\t", "       " + "text".ljust(10) + \
            "unary".ljust(9) + \
            "prefix".ljust(9) + \
            "suffix".ljust(9) + \
            "brace".ljust(9) + \
            "closBr".ljust(9) + \
            "ternary".ljust(9) + \
            "separator".ljust(9))
    for i, tokens in m.tokens.items():
        print(i, end="")
        for item in tokens:
            print("\t", item)
    print("keywords:",m.keywords)
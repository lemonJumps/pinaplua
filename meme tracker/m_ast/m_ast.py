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
        self.tokensByName = {}
        self.tokensByLength = {}

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
                    self.tokensByName[tk.name].append(tk)

        for token in self.tokensByLength:
            if len(token) not in self.tokensByLength:
                self.tokensByLength = []
            self.tokensByLength[len(token)] = token

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

    def parseFile(self, file, encoding = "utf-8"):
        # step 0 - load file
        with pathlib.Path(file).open(encoding=encoding) as f:
            contents = f.read()

        # step 1 - fix source

        # fix new lines so we don't have to deal with all of them
        contents = contents.replace("\n\r", "\n")
        contents = contents.replace("\r\n", "\n")
        contents = contents.replace("\r", "\n")

        lineRemap = [] # keeps new indexes of lines

        # remove line continuation
        if "lineCountinuation" in self.langSpec:
            l = self.langSpec["lineCountinuation"]

            remaps = []
            f = 0
            while True:
                f = contents.find(l + "\n", f+1)
                if f == -1: break
                remaps.append(contents.count("\n", 0, f)+1)

            decrease = 0
            for i in range(contents.count("\n")):
                if i in remaps:
                    decrease += 1
                lineRemap.append(i+1 - decrease)

            contents = contents.replace(l + "\n", " " * (1 + len(l)))


            # contents = contents.replace(l + "\n", " " * (1 + len(l)))
            # contents = contents.replace(l + "\r", " " * (1 + len(l)))
            # contents = contents.replace(l + "\n\r", " " * (2 + len(l)))
            # contents = contents.replace(l + "\r\n", " " * (2 + len(l)))

        # print(lineRemap)

        # print("contents:")
        # print(contents)

        # step 2 - parse file to get nodes

        # step 3 - order nodes by line priority and contents

        # step 4 - process brace nodes

        # step 5 - run all the other nodes

        # return nodes

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

    m.parseFile(ROOT / "ast_test.h")
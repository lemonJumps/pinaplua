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

    string = False

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

class ASTnode:
    token = None
    name = "---"
    type = ""

    line = -1
    character = -1

    braceDepth = 0

    def __str__(self):
        return ("AST[\"{}\" {} : {}, {}]".format(self.name, self.type, self.line, self.character))

    def __repr__(self) -> str:
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

        self.whitespaces = self.langSpec["whitespaces"]
        self.terminator = self.langSpec["terminator"]

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
                            tk.closingBrace = item[6:]
                        elif item[0:5] == "assoc":
                            tk.association = item[6:]
                        elif item[0:6] == "string":
                            tk.string = True
                            tk.closingBrace = item[7:]

                self.tokens[int(id)].append(tk)
                self.tokensByName[tk.text] = tk

        for token in self.tokensByName:
            if len(token) not in self.tokensByLength:
                self.tokensByLength[len(token)] = []
            self.tokensByLength[len(token)].append(token)

        # print(self.tokensByLength)

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
                        tk.closingBrace = item[6:]
                    elif item[0:5] == "assoc":
                        tk.association = item[6:]
                    elif item[0:6] == "string":
                        tk.string = True
                        tk.closingBrace = item[7:]

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

        # create index of lines and index of character on line
        lineIndex = []
        charIndex = []
        line = 1
        character = 1
        for c in contents:
            if c == "\n":
                line += 1
                character = 1
            lineIndex.append(line)
            charIndex.append(character)
            character += 1

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

                contents = contents.replace(l + "\n", " " * (1 + len(l)))

        # remove inline comments
        if "inlineComment" in self.langSpec:
            ic = self.langSpec["inlineComment"]

            # remaps = []
            f = 0
            while True:
                f = contents.find(ic, f+1)
                if f == -1: break
                e = contents.find("\n", f+1)
                contents = (" "*len(contents[f:e])).join([contents[:f], contents[e:]])

        # remove block comments
        if "blockComment" in self.langSpec:
            bc, bc2 = self.langSpec["blockComment"]

            # remaps = []
            f = 0
            f2 = 0
            while True:
                f = contents.find(bc, f+1)
                if f == -1: break
                f2 = contents.find(bc2, f2+1) + len(bc2)
                if f2 == -1: break

                print(f,f2)
                print("\"" + contents[f:f2] + "\"")
                contents = (" "*len(contents[f:f2])).join([contents[:f], contents[f2:]])


        # step 2 - parse file to get nodes
        nodes = []
        braceStack = []
        closingBrace = None
        i = 0
        l = len(contents)
        acc = ""
        while i < l:
            # end data with whitespace
            if contents[i] in self.whitespaces:
                if len(acc) > 0:
                    n = ASTnode()
                    n.name = acc
                    if n.name in self.keywords:
                        n.type = "keyword"
                    else:
                        n.type = "text"
                    n.line = lineIndex[i-len(acc)-1]
                    n.character = charIndex[i-len(acc)-1]
                    nodes.append(n)
                acc = ""
                i+=1
                continue

            acc += contents[i]

            # find terminator
            if self.terminator in acc:
                length = len(self.terminator)
                token = acc[-length:]
                reminder = acc[:-length]
                acc = ""

                # add reminder before the actual node
                if len(reminder) > 0:
                    n = ASTnode()
                    n.name = reminder
                    if n.name in self.keywords:
                        n.type = "keyword"
                    else:
                        n.type = "text"
                    n.line = lineIndex[i-(len(reminder) + len(token))]
                    n.character = charIndex[i-(len(reminder) + len(token))]
                    nodes.append(n)

                n = ASTnode()
                n.name = token
                n.type = "terminator"
                n.line = lineIndex[i-len(token)]
                n.character = charIndex[i-len(token)]
                nodes.append(n)
                
                i+=1
                continue

            # find closing brace
            if closingBrace != None:
                if closingBrace in acc:
                    length = len(closingBrace)
                    token = acc[-length:]
                    reminder = acc[:-length]
                    acc = ""

                    if braceStack:
                        closingBrace = braceStack.pop()
                    else:
                        closingBrace = None

                    # add reminder before the actual node
                    if len(reminder) > 0:
                        n = ASTnode()
                        n.name = reminder
                        if n.name in self.keywords:
                            n.type = "keyword"
                        else:
                            n.type = "text"
                        n.line = lineIndex[i-(len(reminder) + len(token))]
                        n.character = charIndex[i-(len(reminder) + len(token))]
                        nodes.append(n)

                    n = ASTnode()
                    n.name = token
                    n.type = "closingBrace"
                    n.line = lineIndex[i-len(token)]
                    n.character = charIndex[i-len(token)]
                    nodes.append(n)


                    i+=1
                    continue

            # find token
            ordered = list(self.tokensByLength.keys())
            ordered.sort(reverse=True)
            for length in ordered:
                if contents[i:i+length] in self.tokensByLength[length]:
                    token = contents[i:i+length]
                    reminder = acc[:-1]
                    tokenObject : Token = self.tokensByName[token]

                    # add reminder before the actual nodes
                    if len(reminder) > 0:
                        n = ASTnode()
                        n.name = reminder
                        if n.name in self.keywords:
                            n.type = "keyword"
                        else:
                            n.type = "text"
                        n.line = lineIndex[i-(len(reminder) + len(token))]
                        n.character = charIndex[i-(len(reminder) + len(token))]
                        nodes.append(n)

                    if tokenObject.brace:
                        # brace mode
                        if closingBrace != None:
                            braceStack.append(closingBrace)
                        closingBrace = tokenObject.closingBrace
                        n = ASTnode()
                        n.name = token
                        n.token = tokenObject
                        n.type = "brace"
                        n.line = lineIndex[i-len(token)]
                        n.character = charIndex[i-len(token)]
                        nodes.append(n)

                    elif tokenObject.string:
                        # string mode
                        pos = len(acc)-1
                        while True:
                            i+=1
                            acc += contents[i]
                            if contents[i:i+len(tokenObject.closingBrace)] == tokenObject.closingBrace:
                                n = ASTnode()
                                n.name = acc[pos:]
                                n.token = tokenObject
                                n.type = "string"
                                n.line = lineIndex[i-len(n.name)]
                                n.character = charIndex[i-len(n.name)]
                                nodes.append(n)
                                break

                    else:
                        # normal node
                        n = ASTnode()
                        n.name = token
                        n.token = tokenObject
                        n.type = "token"
                        n.line = lineIndex[i-len(token)]
                        n.character = charIndex[i-len(token)]
                        nodes.append(n)

                    # -1 here represents the i pointer moving by one
                    # that's the best explanation I can give atm lmao
                    # TODO explain why this actually works
                    i += length-1
                    acc = ""
            i+=1

        for node in nodes:
            print(node)

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
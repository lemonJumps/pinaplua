from microAST import *
import enum

class States(enum.Enum):
    idle = 0
    number = 1
    text = 2
    string = 3
    brace = 4
    operator = 5 
    special = 6
    end = 7

    preprocessor = 7    

class ASTtypes(enum.Enum):
    expression = 0 # can be any expr
    body = 1 # either function or struct
    type = 2 # typedef
    intType = 3
    function = 4
    variable = 5
    declaration = 6
    itemName = 7
    qualifier = 8



    # funcrion:
    # <qulifiers> [type + *] [name] (param) {body}
    # 
    # function call:
    # [name] (param) ;
    #
    # variable:
    # <qulifiers> [type + *] [name] <=> <value> ;
    #
    # variable use (expression):
    # [name] <=> <value> ;
    # 
    # in order:
    # <qulifiers> [type + *] [name] (param) {body}
    # 
    # [name]
    # <qualifiers> [type + *] 
    #
    #
    #
    #
    #

class ASTstate(enum.Enum):
    idle = 0
    qual_1 = 1
    type_2 = 2
    name_3 = 3
    param_4 = 4
    body_5 = 5
    end_6 = 6

class StackNode:
    def __init__(self) -> None:
        self.parent = None
        self.stack = {}

class CLangParser(Parser):
    def __init__(self) -> None:
        super().__init__()

        self.braceStack = []

        self.state = States.idle
        self.acc = ""

        self.types = {}
        self.definitions = {}

        #current node variables
        # self.parent = None
        # self.nodeStackRoots = []
        # self.currentStackNode = None
        self.ASTstate = ASTstate.idle

    def tokenToNode(self, i, token) -> ASTnode:

        tokenType = token[0]
        tokenText = token[1]
        braceDepth = token[2]


        # distinguish keyword from text
        if tokenType == States.text:
                # is keyword

            # qualifier keyword
            if tokenText in ["const", "volatile", "restrict"]:
                if self.ASTstate in [ASTstate.idle, ASTstate.qual_1]:
                    self.ASTstate = ASTstate.qual_1
                else:
                    print("unexpected qualifier")

            # built in types
            elif tokenText in ["struct", "void", "short", "long", "int", "char", "signed", "unsigned", "size_t", "float", "double"]:
                if self.ASTstate in [ASTstate.idle, ASTstate.qual_1, ASTstate.type_2]:
                    self.ASTstate = ASTstate.type_2
                else:
                    print("unexpected type")

            else:
                if self.ASTstate in [ASTstate.idle, ASTstate.type_2]:
                    self.ASTstate = ASTstate.name_3
                else:
                    print("unexpected name")
                # is name
                pass

        elif tokenType == States.brace:
            if tokenText == ")":
                pass
            elif tokenText == "]":
                pass
            elif tokenText == "}":
                pass 

            elif tokenText == "(":
                pass             
            elif tokenText == "[":
                pass
            elif tokenText == "{":
                pass 

        elif tokenType == States.end:
            # statement has ended, assemble the stack
            pass

        print(self.ASTstate, "\t", tokenText)

        line = i
        priority = 60
        return [line, priority, ASTnode()]




    def accumulateToken(self, char) -> list:

        braceDepth = len(self.braceStack)
        nextState = self.state

        if char == "#":
            nextState = States.preprocessor
        
        elif char in "\n\r" and self.state == States.preprocessor:
            nextState = States.idle


        elif char in "0123456789":
            if self.state in [States.string, States.preprocessor]:
                pass
            else:
                if self.state in [States.idle, States.brace, States.operator, States.special]:
                    nextState = States.number
                # keep being number
                elif self.state == States.number:
                    pass
                # keep being text
                elif self.state == States.text:
                    pass
        
        elif char in "({[":
            if self.state in [States.string, States.preprocessor]:
                pass
            else:
                self.braceStack.append(char)
                nextState = States.brace
        
        elif char in ")}]":
            if self.state in [States.string, States.preprocessor]:
                pass
            else:
                brace = self.braceStack.pop()
                nextState = States.brace

        elif char in "\"\'":
            if self.state in [States.string, States.preprocessor]:
                nextState = States.idle
            else:
                nextState = States.string

        elif char in "`~@!$^*%&<>+=_–|/\:,.?":
            if self.state in [States.string, States.preprocessor]:
                pass
            else:
                if self.state == States.special:
                    pass
                else:
                    nextState = States.special
        elif char in " \t\n\r":
            if self.state in [States.string, States.preprocessor]:
                pass
            else:
                nextState = States.idle
        elif char in ";":
            if self.state in [States.string, States.preprocessor]:
                pass
            else:
                nextState = States.end
        else:
            if self.state in [States.string, States.preprocessor]:
                pass
            else:
                nextState = States.text

        ret = []

        if nextState != self.state:
            ret = [[self.state, self.acc, braceDepth]]
            self.acc = ""
            self.state = nextState
        
        self.acc += char

        return ret
    

        # funcrion:
        # <qulifiers> [type + *] [name] (param) {body}
        # 
        # function call:
        # [name] (param) ;
        #
        # variable:
        # <qulifiers> [type + *] [name] <=> <value> ;
        #
        # variable use (expression):
        # [name] <=> <value> ;
        # 
        # in order:
        # <qulifiers> [type + *] [name] (param) {body}
        # 
        # [name]
        # <qualifiers> [type + *] 
        #
        #
        #
        #
        #

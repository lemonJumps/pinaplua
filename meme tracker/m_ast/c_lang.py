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

    preprocessor = 8

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
    idle        = 0



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

        self.ASTstateStack = []
        self.ASTstate = ASTstate.idle
        self.ASTdepth = 0

        self.currentAST = None
        self.ASTstack = []
        self.texts = []

    def tokenToNode(self, i, token) -> ASTnode:

        tokenType = token[0]
        tokenText = token[1]
        braceDepth = token[2]

        if tokenType == States.idle:
            return None

        
        if tokenType == States.text:
            self.texts.append(tokenText)

        if braceDepth > self.ASTdepth:
            self.ASTstack.append(self.currentAST)
            self.ASTstateStack.append(self.ASTstate)
            self.ASTdepth = braceDepth
            

            if tokenText == "(":
            

        elif braceDepth < self.ASTdepth:
            # on pop save to current ast node IG lol
            self.currentAST = self.ASTstack.pop()
            self.ASTstateStack.pop()
            
            self.ASTdepth = braceDepth
        else:
            pass

        print("\t" * braceDepth, tokenType, tokenText)
        # print(self.ASTstateStack)

        return None




    def accumulateToken(self, char) -> list:

        updateToken = False

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
                updateToken = True # token can only be 1 character
        
        elif char in ")}]":
            if self.state in [States.string, States.preprocessor]:
                pass
            else:
                brace = self.braceStack.pop()
                nextState = States.brace
                updateToken = True # token can only be 1 character

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

        if nextState != self.state or updateToken == True:
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

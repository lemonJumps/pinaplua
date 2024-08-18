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


class LangNode():
    def __init__(self, depth, line) -> None:
        self.depth = depth
        self.line = line
        self.texts = []
        self.hasType = False
        self.hasName = False
        self.hasArguments = False
        self.hasBody = False
        self.inArguments = False

    def __str__(self) -> str:
        return "Node {} at line {}, depth {}".format(self.texts, self.line, self.depth)

class CLangParser(Parser):
    def __init__(self) -> None:
        super().__init__()

        self.braceStack = []

        self.state = States.idle
        self.acc = ""

        self.types = {}
        self.definitions = {}

        self.currentNode = None
        self.nodeStack = []

        self.rootNode = None
        self.orphanedASTnodes = []

        self.ASTdepth = 0

    def tokenToNode(self, i, token):

        tokenType = token[0]
        tokenText = token[1]
        braceDepth = token[2]

        if tokenType == States.idle:
            return None

        def endOfNode():
            cn = self.currentNode
            if len(cn.texts) > 1:
            
                if self.ASTdepth == 0:
                    self.rootNode = ASTnode(cn.texts[-1], "dunno", cn.texts[0:-1])
                else:                
                    self.orphanedASTnodes.append(ASTnode(cn.texts[-1], "dunno", cn.texts[0:-1]))
            

        if self.currentNode == None:
            self.currentNode = LangNode(braceDepth, i)

        if braceDepth > self.ASTdepth:
            hasArguments = self.currentNode.hasArguments
            self.nodeStack.append(self.currentNode)
            self.currentNode = LangNode(braceDepth, i)
            self.ASTdepth = braceDepth

        if tokenType == States.text:
            self.currentNode.texts.append(tokenText)


        elif braceDepth < self.ASTdepth:
            # TODO close lang node and make an AST node out of it

            endOfNode()

            self.currentNode = self.nodeStack.pop()
            self.ASTdepth = braceDepth

        if tokenText == ")":
            self.currentNode.hasArguments = True
            
        if tokenText == "}":
            self.currentNode.hasBody = True

        print("\t" * braceDepth, self.currentNode)

        if tokenType == States.end:
            endOfNode()
            self.currentNode = LangNode(braceDepth, i)

        # occurs at the end of function declaration
        if tokenType == States.brace and tokenText == "}" and \
        len(self.currentNode.texts) > 1 and \
        self.currentNode.hasArguments == True and \
        self.currentNode.hasBody == True:
            
            endOfNode()
            self.currentNode = LangNode(braceDepth, i)

        # occurs in the middle of function arguments
        if tokenType == States.special and tokenText == ",":
            endOfNode()
            self.currentNode = LangNode(braceDepth, i)

        if self.rootNode != None:
            rn = self.rootNode
            self.rootNode = None
            return rn

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
            if self.acc in "({[":
                braceDepth = braceDepth -1    
            ret = [[self.state, self.acc, braceDepth]]
            self.acc = ""
            self.state = nextState
        
        self.acc += char

        return ret
    
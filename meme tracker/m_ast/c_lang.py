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
    end = 6

    preprocessor = 7    

class CLangParser(Parser):
    def __init__(self) -> None:
        super().__init__()

        self.braceStack = []

        self.state = States.idle
        self.acc = ""

    def tokenToNode(self, i, token) -> ASTnode:
        line = i
        priority = 60
        return [line, priority, ASTnode()]

    def accumulateToken(self, char) -> list:

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

        elif char in "`~@!$^*%&<>+=_–|/\;:,.?":
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

        if nextState != self.state:
            print("")
            print(self.state, "->", nextState, ": ", end = "")
            self.state = nextState
            if nextState == States.brace:
                print(self.braceStack, end = "")

        print(char, end = "")

        return []
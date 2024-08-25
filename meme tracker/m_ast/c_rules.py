from m_ast import ASTnode

class Rules:
    def __init__(self) -> None:
        print("rules loaded")
    
    def isNodeSeparate(self, previousNodes :list[ASTnode], node :ASTnode, nextNodes :list[ASTnode], depth:int):
        if depth == 0:
            if node.type == "closingBrace" and node.name == "}":
                return True

        return False

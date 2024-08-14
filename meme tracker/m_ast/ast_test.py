from c_lang import CLangParser, States
from pathlib import Path

ROOT = Path(__file__).parent

if __name__ == "__main__":
    parser = CLangParser()

    parser.parseFile(ROOT / "ast_test.h")

    for i in parser.tokens:
        if i[0] != States.idle:
            print(i)

    # print(parser.tokens)
    # print(parser.roots)
    


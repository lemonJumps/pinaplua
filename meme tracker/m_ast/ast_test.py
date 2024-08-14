from c_lang import CLangParser
from pathlib import Path
ROOT = Path(__file__).parent

if __name__ == "__main__":
    parser = CLangParser()

    parser.parseFile(ROOT / "ast_test.h")

    # print(parser.tokens)
    # print(parser.roots)
    


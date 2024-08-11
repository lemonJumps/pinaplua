import clang.cindex as cindex
import clang


import pathlib

TU_None = 0x0
TU_DetailedPreprocessingRecord = 0x01
TU_Incomplete = 0x02
TU_PrecompiledPreamble = 0x04
TU_CacheCompletionResults = 0x08
TU_ForSerialization = 0x10
TU_CXXChainedPCH = 0x20
TU_SkipFunctionBodies = 0x40
TU_IncludeBriefCommentsInCodeCompletion = 0x80
TU_CreatePreambleOnFirstParse = 0x100
TU_KeepGoing = 0x200
TU_SingleFileParse = 0x400
TU_LimitSkipFunctionBodiesToPreamble = 0x800
TU_IncludeAttributedTypes = 0x1000
TU_VisitImplicitAttributes = 0x2000
TU_IgnoreNonErrorsFromIncludedFiles = 0x4000
TU_RetainExcludedConditionalBlocks = 0x8000 



class CParser:
    def __init__(self) -> None:
        self.tokens = {}
        self.tokensByLine = {}
        self.dbgHintsByLine = {}

    def parseFile(self, fileName):
        if fileName not in self.tokens:
            # with pathlib.Path(fileName).open("r", encoding="utf-8") as f:
            #     contents = f.read()

            idx = cindex.Index.create()
            tu = idx.parse(fileName, options=TU_KeepGoing | TU_SingleFileParse)
            self.tokens[fileName] = list(tu.get_tokens(extent=tu.cursor.extent))

            self.tokensByLine[fileName] = {}
            self.dbgHintsByLine[fileName] = {}
            for token in self.tokens[fileName]:
                token : cindex.Token

                line = token.location.line
                if line not in self.tokensByLine[fileName]:
                    self.tokensByLine[fileName][line] = []
                    self.dbgHintsByLine[fileName][line] = []

                self.tokensByLine[fileName][line].append(token)

                self.dbgHintsByLine[fileName][line].append(str(token.kind) + " " + str(token.spelling) + " " + str(token.cursor.spelling))

    
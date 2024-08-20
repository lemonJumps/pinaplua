# micro ast subproject

Subproject of meme tracker and pinaplua. </br>
Aims to be a small and fast, abstract syntax tree generator.

## important note
micro AST doesn't provide any error checks, it simply processes code as it comes.

If micro AST is used as a front-end to a compiler, the error checking must be done by the software that uses micro AST.

## usage:


### tokens.json

`tokens.json` is a file describing the language that is supposed to be processed.

Currently `c_tokens.json` is provided, as an example, implementing C98 version of C.
This is also the version of c that the pinaplua VM needs lol.

#### Field refference:

`langName` - describes which language is used (C, C++ etc.)</br>
This field is not really used it's there for convenience of the users and can be any string value.

`version` - language version, describes the version of language implemented</br>
Same as above, isn't really used in micro AST

`fileVersion` - says which file version this file has been made for. </br>
Required for future proofing, will display an error if file is mismatched with mAST. In the future mAST should be able to automatically fix files which are made for next versions.
or maybe not lol, we'll see XD

`langSpec` - contains language specifications
- `line Continuation` - in string is in fron of new line, new line and this string will be replaced by spaces before tokenization
- `inlineComment` - any characters after this string will be replaced by spaces tokenization
- `block`- any characters betweeen strings will be replaced by spaces before tokenization
- `terminator` - if terminator is defined, it will forcefully end line of tokens </br>
For languages like C the terminator is `;`, and for languages like python it's `\n`
- `whitespaces` - contains characters that will be treated as whitespaces.

`tokens` - contains tokens grouped by priority </br>

```json
    "0":[
        ["++", "suffix", "unary"],
        ["--", "suffix", "unary"],
        "+", "."
    ]
```
Example of tokens with priority 0. The lower the priority the sooner the token will get processed, bu that also means the lower it will be placed in the tree.

#### Tokens and their structure

Tokens are stored either as a single string which contains the name of the token, or as a list containing its parameters.

Parameters:

Please note all parameters can be combined ***HOWEVER*** there's no guarantee all of them will be executed and in what order.

- `unary`, `prefix`, `postfix` - when defined associated AST node will only consume node in front and in the back.</br>
prefix means the current node **is the prefix**, so it will consume the node behind it.
A suffix node will consume the node in front.
- `brace:<n>` - when defined, associated AST node will take any nodes that are contained inside of it as it's children.</br>
the `<n>` is the closing brace
- `string:<n>` - when defined, associated node will take the entirety on characters between the **token name** and `<n>`, and store them as a string in the **node name**.
- `separator` - works like terminator.
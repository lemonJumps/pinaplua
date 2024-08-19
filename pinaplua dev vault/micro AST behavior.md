# Tokens vs keywords
Tokens in mAST don't cover every single possibility, but rather only cover expressions.
Where mAST will simply assign a priority to them and create tokens from them.

### parsing process steps:
0. loading language json
	- Technically not a step
	- Loads parameters from json to Token objects
1. source is altered to remove (replace with spaces) any special characters like comments, block comments and line continuations. 
2. file is parsed linearly, and each valid text is replaced by a node
3. nodes are ordered by line and priority
4. brace nodes consume all nodes starting between it self and and the position of closing brace
5. each node consumes adjacent nodes and/or nodes contained in these nodes

### Consuming tokens
Node will consume other nodes based on their position and it's own properties.
For instance a brace node doesn't usually consume parameters outside of it, but a normal operator will consume both left and right node.
### Token properties:
- priority - sets precendence of tokens, tokens with lower priority will be processed first
- association - tells the mAST if nodes are processed left to right or right to left
- unary - consumes only one node
- prefix - consumes node after an expression (meaning this node is after the node it consumes I.e. suffix)
- suffix - consumes node before expression (meaning this node is before the node it consumes I.e. suffix)
- brace - consumes nodes between it's text and closingBrace, during parsing this node places all of it's contents into it's own buffer
- closingBrace - contains the other brace to look for
- ternaryCond - consumes anything between and around ternary condition characters
- separator - skips creating a node and rather assigns node to the left to the parent node
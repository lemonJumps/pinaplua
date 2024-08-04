# WELCOME! TO PINAPLE LUA or PINAPLUA

## what is pinaplua?
I'm glad you asked! it's an extension to the lua language! It's made in a way where it allows compatibility with lua 5.4
But adds important functionality like type safety, multiple types, and a built in ffi!

This repository also contains both a standalone app as well as embeddable code!

## currently planned features:
- [ ] standalone interpreter
- [ ] FFI
- [ ] Ctypes style foreign library calls
- [ ] c++ name demangling
- [ ] custom types (uint8_t etc...)
- [ ] type conversions and safety
- [ ] python style tokenizer

## build support:
- [ ] windows build
- [ ] android crossbuild

## Q&A
- why not use luau?
    Because luau doesn't offer byte specific types, so I'll have to do these my self anyway.
    So I find it easier to just start from bare lua.

- with the FFI will I need to compile my code?
    Most likely yes, I'm planning on the ffi to use a gcc / LLVM compiler to create the frontend.
    But who knows It might be easier to make my own compiler.

- what platforms are supported?
    Windows and linux.
    Mac is too hostile to do any development on and honestly, it's a platform that is used by a tiny fraction of people, so I won't bother.
    If anyone wants to add mac support them selves, if you make a pull request, I'll definitely add it :D

- what's python style tokenizer?
    Basically just a way to use python syntaxe instead of lua. I preffer python more so I wanted to have that option.
    But who knows maybe lua will grow on me.

- what's next?
    Well, games really, and bunch of software to support these games.
    I'm honeslty tired of having to deal with python not being crosscompilable in almost any capacity, and C# requiring several wrappers in order to simply work.
    So the next thing is going to be using this for OpenCV.
    And adding OpenCV functionality to godot, to finally allow me to make a simple 3d scanner.

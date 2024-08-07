# WELCOME! TO PINAPLE LUA or PINAPLUA

🚧 Under construction: pinaplua is still not in operational state 🚧</br>
please be patient with me, and star the repository if you want to recieve updates :D

## what is pinaplua?
I'm glad you asked! Two parts, or ehm 3! actually. </br>

pinapple the Virtual machine! made to be code, machine and system independent!

pinaplua the lua language! It's made in a way where it allows compatibility with lua 5.4,
But adds important functionality like type safety, multiple types, and a built in ffi!

And Pizza!!! the pinaple interactive shell :D (get it, cause you can have pineapple on pizza flkjfgdf)

This repository also contains both a standalone app as well as embeddable code!

## why is pinaplua
Pinaplua serves to fill one simple hole, fix one simple issue, and that is that **THERE'S NO EASY SCRIPTING LANGUAGE/TOOL THAT JUST ALLOWS PPL TO GLUE TOGETHER LIBRARIES AND APPS**.

But what about python? python is pretty universal right? Yeah, until you have to build python and discover what a chore it is to configure it's fragmented code base.

Then what about C#? yeah C# is nice and core runs almost everywhere, except that creating wrappers for non C# code requires your code to be split between 3 different places.

and I could go on and on.

But the two main advantages are, that the VM literally only calls functions, and is so low level that it only requires malloc, calloc and free to run.

And that I can literally use any language I please, as long as I write lexer for it.

## currently planned features:
- [ ] pinapple VM
- [ ] pinaplua style tokenizer
- [ ] standalone interpreter
- [ ] windows safety net
- [ ] linux safety net
- [ ] FFI
- [ ] Ctypes style foreign library calls
- [ ] c++ name demangling
- [ ] Multithreading / Multiprocessing
- [ ] custom types (uint8_t etc...)
- [ ] type conversions and safety
- [ ] python style tokenizer
- [ ] lua plugin loading
- [ ] python plugin loading

## build support:
- [ ] windows build
- [ ] android crossbuild
- [ ] FFI builds for both windows and android
- [ ] linux build + FFi

## features that would be nice:
- [ ] x86 to amd64 bridge for FFI
- [ ] x86 to amd64 bridge for Foreign library calls

## Q&A

- with the FFI will I need to compile my code?</br>
    Yes but only the front facing interface, I'm planning on the ffi to use a gcc / LLVM compiler to create the frontend.
    But who knows It might be easier to make my own compiler.
    But besides that front facing interface, everything else can be scripted.
    So if you are on a platform that doesn't make it easy to build the interface, you can just pre build one and it'll stay the same.

- what platforms are supported?</br>
    Windows and linux.
    Mac is too hostile to do any development on and honestly, it's a platform that is used by a tiny fraction of people, so I won't bother.
    If anyone wants to add mac support them selves, if you make a pull request, I'll definitely add it :D
    That said it shouldn't be hard to port the code to any platform as long as there's at least a c compiler for it

- what's python style tokenizer?</br>
    Basically just a way to use python syntaxe instead of lua. I preffer python more so I wanted to have that option.
    But who knows maybe lua will grow on me.
    It also plays into the idea that you should be able, (sometime in the future) to just take a python package and run it in pinaple.

- what's next?</br>
    Well, games really, and bunch of software to support these games.
    I'm honeslty tired of having to deal with python not being crosscompilable in almost any capacity, and C# requiring several wrappers in order to simply work.
    So the next thing is going to be using this for OpenCV.
    And adding OpenCV functionality to godot, to finally allow me to make a simple 3d scanner.

- is pinaplua safe?</br>
    There's actually multiple parts to this:

    - pineaple vm:</br>
        The pineaple vm has safequards that check if internally if usage of the vm is correct, which should make the internals work safely.
        HOWEVER, there is no way of testing if what you tell it to do is *correct*.
        If you give it a random address and say this is a function, It will treat it as a function.
        It also doesn't have a way of checking for hartbleed, race conditions etc.
    
    - Intermediary libraries / modules:</br>
        These can and should contain safeguards, which should make these safe.
        So array access, creating/destroying objects should be fine,
        and should return an error if anything goes wrong.

    - Pinaplua / Pithon:</br>
        Safe guards on this level are built into the language, and it's underlying implementation.
        So it will be as safe as the language specification allows.

- What's a safety net?</br>
    It's an abstraction of underlying systems safety features.
    for *operating systems* like *windows and linux* it's stuff like error handling.
    Where if something happens, the system will report an error to the application.
    This can be used to *safely stop the application*, collect logs and display the error.
    
    Hopefully this should let the script reat to a fatal error too, but that solely depends on the kind of error that occured.

    When used on bare metal, It's slightly different, here the vm needs to handle *hardware faults*.
    I'd imagine that on different ARM cpus it's going to be relatively easy to handle hard faults.
    But any hardware faults have to be implemented on case to case bases, as theres no unified architecture to those.
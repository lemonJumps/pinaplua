# oh god not another build system, don't we have enough??

Don't worry, this one is simple. </br>
In the root you'll find `unitTest.py` `build.py` and `build.json`

All you have to do is run these with python, **unitTest** will build, the unit test, and run it, this is used for development, but can be used to see if every part of pinaplua is working on your system.

### requirements
- gcc or llvm (MSVC maybeeee in the future)
- python3

### custom builds
If you want to make a custom build, it's also easy.

All you need is to edit, the targets in `build.json`.

Here's what it's contents mean:
- archBased - architecture specific files, these are based on pythons platform.machine and platform.system, separated by an underscore, for example:`AMD64_Windows`
- folders - folders to be searched for .h .c and .s files. .h files are treated as headers everything else is passed as a source file.
- buildFolder - where to place temporary build files
- buildFlags - flags for the build :P
- output - the name of executable to be created

### building with make, cmake, etc..
For these essentially just pick a file from the "architecture dependent" folder, based off of your target, and build the rest like normal.
Mind you the code is written to expect all the files in the "virtual root" so either build pinaple as it's own static library, or add -Ipinaple as the header folder :P


### -w- ok but why?
it's because there's so much potential for variation with make on windows and other platforms.
Plus make is kinda outdated with syntax that encourages heavy wizardry, so just having a small python script that does the same and is waay more portable.

### does compiler matter?
Well yes, but actually no.
If you want to run 64 bit architectures, you need a 64 bit build, But other then that, pinaple can call any kind of call, as long as the process and the cpu run in a compatible mode to call whatever you need to call.

### Will it work with my \<insert obscure architecture here>
Yes, you have to write a custom caller tho, simillar to the contents of `architecture dependent`
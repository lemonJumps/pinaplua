## Collection of advanced usecases (not hard really lol)

### Usecase #1: make this old software work with new library
#### Problem:
Woah!, you've been asked to make a software written for windows 95 run on windows 10 with new libraries.

But OH NO!!! we don't have any compilable sourcecode, because this thing was written 30 years ago. And because this is a aerospace projects, this ancient software does something we simply cannot live without.

#### Solution:
1. Use pinaple to create an FFI intermediary with every library that the app is acessing.
2. Use a simple script to capture data (running on the original system).
3. Decide what data to change, and what libraries to replace.
4. Use python/lua with pinaple to adapt the old calls to the new libraries.
5. Package the lua script into the FFI, or keep it separate
6. Ship app with new libraries.

### Usecase #2: terrible library API
#### Problem:
You have a library, like OpenCV and the library is massive, enormous even, writing a c++ interface by hand will take forever!

And the game engine you want to use isn't really friendly towards implementing external libraries.

The C# version binding isn't fully featured and you can't use python.

#### Solution:
1. Use pinaple to automatically create a binding for OpenCV lib/dll
2. Create an FFI interface for the native extension/plugin **OR** integrate pineaple into engine.
3. Write small functions to patch differeces between two codebases.
4. Ship game with newly implemented library

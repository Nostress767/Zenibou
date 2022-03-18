This is a simple engine for starting a window, capturing inputs and drawing pixels to the screen. At the moment it can only run on Microsoft Windows.

building raylib from source on windows
--------------
First, clone my [raylib fork](https://github.com/Nostress767/raylib).
Then, using [Visual Studio 2022 Developer Command Prompt](https://visualstudio.microsoft.com/downloads/?q=build+tools) with vcvarsall.bat Environment initialized for: 'x86', change directory to src/ and run:

    nmake

This should make raylib.lib on the current directory, copy that to Zenibou/raylib/lib/ or just change the Makefile accordingly.

If you want to compile for web with raylib.a, build it using:

    nmake web

And copy that to the same place as raylib.lib.

building the example on windows
--------------
Make sure first you have raylib includes and raylib.lib on raylib/include and raylib/lib respectively before compiling.

Using [Visual Studio 2022 Developer Command Prompt](https://visualstudio.microsoft.com/downloads/?q=build+tools) with vcvarsall.bat Environment initialized for: 'x86' to compile, simply run:

    nmake

You can also compile for [raylib](https://www.raylib.com/), but this will require you to change up the MSVCMakefile to include the correct paths for the "include" and "lib" folders (and to compile/install raylib, of course).
After doing so, you may run:

    nmake ray

You can also compile for web now! To do so, get emscripten SDK (you may follow [raylib's guide](https://github.com/raysan5/raylib/wiki/Working-for-Web-(HTML5))), and python to be able to serve http on localhost.
Now, just run:

    nmake web

How this project came to be:

[Win32-Drawing-Pixels](https://samulinatri.com/blog/win32-drawing-pixels/)

[Handmade Hero](https://handmadehero.org/)

[This channel](https://www.youtube.com/channel/UCaTznQhurW5AaiYPbhEA-KA)

[One Lone Coder's PixelGameEngine](https://github.com/OneLoneCoder/olcPixelGameEngine)

[raylib](https://github.com/raysan5/raylib)

[mackron's miniaudio](https://github.com/mackron/miniaudio)


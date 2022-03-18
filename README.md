This is a simple engine for starting a window, capturing inputs and drawing pixels to the screen. At the moment it can only run on Microsoft Windows.

Using [Visual Studio 2022 Developer Command Prompt](https://visualstudio.microsoft.com/downloads/?q=build+tools) with vcvarsall.bat Environment initialized for: 'x86' to compile, simply run:

    nmake /FMSVCMakefile

You can also compile for [raylib](https://www.raylib.com/), but this will require you to change up the MSVCMakefile to include the correct paths for the "include" and "lib" folders (and to compile/install raylib, of course).
After doing so, you may run:

    nmake /FMSVCMakefile ray

How this project came to be:

[Win32-Drawing-Pixels](https://samulinatri.com/blog/win32-drawing-pixels/)

[Handmade Hero](https://handmadehero.org/)

[This channel](https://www.youtube.com/channel/UCaTznQhurW5AaiYPbhEA-KA)

[One Lone Coder's PixelGameEngine](https://github.com/OneLoneCoder/olcPixelGameEngine)

[raylib](https://github.com/raysan5/raylib)

[mackron's miniaudio](https://github.com/mackron/miniaudio)


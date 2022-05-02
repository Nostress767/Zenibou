This is a single include file for starting a window, capturing inputs and drawing pixels to the screen. At the moment it can only run on Microsoft Windows.

building the example from source on windows with MinGW
--------------
Easy, just run (double click) open_venv.bat and a terminal (it's actually [Christopher Wellons's w64devkit](https://github.com/skeeto/w64devkit)) should pop up (on first execution takes anywhere between 10 seconds to 1 minute depending on various conditions and requires internet access).

On the new terminal, simply run:

    make

Now just run the example (./Example.exe).

If you wish to compile with raylib as backend, you need to build it from source first.

building raylib from source on windows with MinGW
--------------
Run open_venv.bat, from there run:

    make raylib

This should build raylib.lib and place it on lib/, now simply run:

    make ray

Proceed as usual (./Example.exe).

building the example on GNU/Linux
--------------
Make sure -lGL works/is installed (on ubuntu install libgl1-mesa-dev).

Git clone this repository (or download it) and build raylib, like this:

    make linuxraylib

Then, build the example:

    make linux

Now just run it:

    ./Example


How this project came to be/inspirations/copy pastes:
--------------

[Win32-Drawing-Pixels](https://samulinatri.com/blog/win32-drawing-pixels/)

[Handmade Hero](https://handmadehero.org/)

[This channel](https://www.youtube.com/channel/UCaTznQhurW5AaiYPbhEA-KA)

[One Lone Coder's PixelGameEngine](https://github.com/OneLoneCoder/olcPixelGameEngine)

[raylib](https://github.com/raysan5/raylib)

[mackron's miniaudio](https://github.com/mackron/miniaudio)

[skeeto's asteroids](https://github.com/skeeto/asteroids-demo) and [w64devkit](https://github.com/skeeto/w64devkit) (used in this project!)

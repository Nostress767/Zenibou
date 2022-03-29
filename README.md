This is a simple engine for starting a window, capturing inputs and drawing pixels to the screen. At the moment it can only run on Microsoft Windows.

building the example from source on windows with MinGW
--------------
Easy, just run (double click) install.bat, then run open_venv.bat and a terminal (it's actually [Christopher Wellons's w64devkit](https://github.com/skeeto/w64devkit)) should pop up (on first execution takes anywhere between 10 seconds to 1 minute depending on various conditions and requires internet access).

On the new terminal, simply run:

    make

Now just run the example (./Example.exe).

If you with to compile with raylib as backend, you need to build it from source first.

building raylib from source on windows with MinGW
--------------
Run open_venv.bat, from there run:

    make raylib

This should build raylib.lib and place it on lib/, now simply run:

    make ray

Proceed as usual (./Example.exe).

building the example from source on windows with MSVC
--------------
Run install_msvc.bat(UNTESTED) and wait for it to finish. Then run open_venv_msvc.bat, this should open the Visual Studio Developer Command Prompt. Now run:

    nmake

To use raylib, compile it first with:

    nmake raylib

And then:

    nmake ray

If you want to compile for we, first get emscripten SDK (you may follow [raylib's guide](https://github.com/raysan5/raylib/wiki/Working-for-Web-(HTML5))), and python to be able to serve http on localhost. After that, build webraylib.a using:

    nmake webraylib

And then:

    nmake web


building the example on GNU/Linux (untested)
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

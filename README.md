This is a single include file for starting a window, capturing inputs and drawing pixels to the screen. It compiles to Windows and Linux. 

Building the example from source on windows with MinGW 
--------------
Make sure you have [DirectX User Runtime](https://www.microsoft.com/en-us/download/details.aspx?id=35) installed. 

Open open_venv.bat and a new terminal should pop up. 

On the new terminal, simply type: 

    make

Building the example on GNU/Linux
--------------
Make sure that you have your distribution's equivalent of [Xlib](https://www.x.org/wiki/) and Xinput:
- libx11-dev and libxi-dev on Ubuntu
- libX11-devel and libXi-devel on Fedora

Also make sure to have GNU Make and GCC installed.

Then, on a terminal just run:

    make

Documentation
--------------

Over at the [Wiki](https://github.com/Nostress767/Zenibou/wiki).

References:
--------------

[Win32-Drawing-Pixels](https://samulinatri.com/blog/win32-drawing-pixels/)

[Handmade Hero](https://handmadehero.org/)

[Molly Rocket](https://www.youtube.com/channel/UCaTznQhurW5AaiYPbhEA-KA)

[PixelGameEngine](https://github.com/OneLoneCoder/olcPixelGameEngine)

[raylib](https://github.com/raysan5/raylib)

[miniaudio](https://github.com/mackron/miniaudio)

[asteroids](https://github.com/skeeto/asteroids-demo)

[w64devkit](https://github.com/skeeto/w64devkit) (used in this project!)

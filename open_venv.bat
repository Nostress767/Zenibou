cd external
if not exist w64devkit curl -L --output w64devkit.zip --url https://github.com/skeeto/w64devkit/releases/download/v1.11.0/w64devkit-i686-1.11.0.zip
if not exist w64devkit tar -xf w64devkit.zip
if exist w64devkit.zip del w64devkit.zip
start w64devkit\w64devkit.exe

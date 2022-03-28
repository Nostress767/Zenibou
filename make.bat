curl -L --output vs_buildtools.exe --url https://aka.ms/vs/17/release/vs_buildtools.exe
vs_buildtools.exe --quiet --add Microsoft.VisualStudio.Workload.VCTools
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars32.bat"
if exist vs_buildtools.exe del vs_buildtools.exe

curl -L --output vs_buildtools.exe --url https://aka.ms/vs/17/release/vs_buildtools.exe
vs_buildtools.exe --quiet --add Microsoft.VisualStudio.Workload.VCTools
if exist vs_buildtools.exe del vs_buildtools.exe

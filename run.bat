@echo off
echo Now compiling...

if /i "%1"=="Release" (
  REM // Release
  g++ -Os -o ciscoSim.exe Source.cpp resource.o^
   && strip --strip-all ciscoSim.exe
) else (
  REM // Debug
  g++ -o ciscoSim.exe Source.cpp resource.o
)

echo %* | find /I "Run" >nul
if not errorlevel 1 (
  start ciscoSim.exe
)

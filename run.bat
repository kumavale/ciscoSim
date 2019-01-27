@echo off
echo Now compiling...

echo %* | find /I "Release" >nul
if not errorlevel 1 (
  REM // Release
  g++ -Os -o ciscoSim.exe main.cpp -std=c++11 resource.o^
   && strip --strip-all ciscoSim.exe
  if errorlevel 1 (
    exit /B 1
  )
) else (
  REM // Debug
  g++ -o ciscoSim.exe main.cpp -std=c++11 resource.o
  if errorlevel 1 (
    exit /B 1
  )
)

echo %* | find /I "Run" >nul
if not errorlevel 1 (
  start ciscoSim.exe
)

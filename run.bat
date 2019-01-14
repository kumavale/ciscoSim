@echo off
echo Now compiling...

if /i "%1"=="Release" (
  REM // Release
  g++ -Os -o ciscoSim.exe Source.cpp resource.o^
   && strip --strip-all ciscoSim.exe
) else if /i "%1"=="Run" (
  g++ -o ciscoSim.exe Source.cpp resource.o^
   && start ciscoSim.exe
) else (
  REM // Debug
  g++ -o ciscoSim.exe Source.cpp resource.o
)

if /i "%2"=="Run" (
  start ciscoSim.exe
)

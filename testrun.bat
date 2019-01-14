@echo off
echo Now compiling...

REM // Release
REM g++ -Os -o ciscoSim.exe Source.cpp resource.o^
REM  && strip --strip-all ciscoSim.exe^
REM  && start ciscoSim.exe

REM // Debug
g++ -o ciscoSim.exe Source.cpp resource.o^
  && start ciscoSim.exe

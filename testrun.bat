@echo off
echo Now compiling...
g++ -Os -o ciscoSim.exe Source.cpp resource.o^
 && strip --strip-all ciscoSim.exe^
 && start ciscoSim.exe

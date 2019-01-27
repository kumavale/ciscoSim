#!/bin/bash
echo "Now compiling..."

if [ `echo $* | grep -i Release` ]; then
  # Release
  g++ -Os -o ciscoSim main.cpp -std=c++11 resource.o \
   && strip --strip-all ciscoSim \
   || exit 1
else
  # Debug
  g++ -o ciscoSim main.cpp -std=c++11 resource.o \
   || exit 1
fi

if [ `echo $* | grep -i Run` ]; then
  ./ciscoSim
fi
